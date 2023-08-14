#include <math.h>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "RaycastRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "GameData.h"
#include "RenderData.h"
#include "SFMLWindow.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RaycastRenderer::RaycastRenderer( shared_ptr<GameConfig> gameConfig,
                                  shared_ptr<RenderConfig> renderConfig,
                                  shared_ptr<GameData> gameData,
                                  shared_ptr<RenderData> renderData,
                                  shared_ptr<SFMLWindow> window ) :
   _gameConfig( gameConfig ),
   _renderConfig( renderConfig ),
   _gameData( gameData ),
   _renderData( renderData ),
   _window( window )
{
   _renderColumns = (sf::Vertex*)malloc( sizeof( sf::Vertex ) * gameConfig->ScreenWidth * 2 );

   auto screenWidth = (float)gameConfig->ScreenWidth;
   auto screenHeight = (float)gameConfig->ScreenHeight;

   _floorRenderRect[0] = Vertex( Vector2f( 0, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[1] = Vertex( Vector2f( screenWidth, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[2] = Vertex( Vector2f( screenWidth, screenHeight ), Color( 22, 59, 8 ) );
   _floorRenderRect[3] = Vertex( Vector2f( 0, screenHeight ), Color( 22, 59, 8 ) );

   _skyPosition = Vector2f( 0, 0 );
   _skyTextureRect = IntRect( 0, 0, gameConfig->ScreenWidth, gameConfig->ScreenHeight );

   _spriteTextureRect.top = 0;
   _spriteTextureRect.width = 1;
   _spriteTextureRect.height = 1080;

   _spriteVerticalScale.x = 1;
}

RaycastRenderer::~RaycastRenderer()
{
   delete _renderColumns;
   _renderColumns = nullptr;
}

void RaycastRenderer::RenderCeilingAndFloor()
{
   // MUFFINS: the sky should rotate with the player, figure that one out
   auto skySprite = _renderData->GetSpriteById( _renderConfig->SkySpriteId );
   skySprite.setPosition( _skyPosition );
   skySprite.setTextureRect( _skyTextureRect );
   _window->Draw( skySprite );

   _window->Draw( _floorRenderRect, 4, Quads );
}

void RaycastRenderer::RenderLineseg( const Lineseg& lineseg,
                                     float drawStartAngle,
                                     int startColumn,
                                     int endColumn )
{
   auto player = _gameData->GetPlayer();
   auto playerPosition = player->GetPosition();
   auto playerAngle = player->GetAngle();
   static Vector2f pIntersect;

   for ( int i = startColumn, j = 0; i <= endColumn; i++, j++ )
   {
      auto drawAngle = drawStartAngle - ( j * _renderConfig->FovAngleIncrement );
      NORMALIZE_ANGLE( drawAngle );
      auto doesIntersect = Geometry::RayIntersectsLine( playerPosition, drawAngle, lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, &pIntersect );

      // this often happens around the edge of a lineseg, in which case we can just draw the edge
      if ( !doesIntersect )
      {
         if ( i == startColumn || i == startColumn + 1 )
         {
            pIntersect.x = lineseg.start.x;
            pIntersect.y = lineseg.start.y;
         }
         else if ( i == endColumn || i == endColumn - 1 )
         {
            pIntersect.x = lineseg.end.x;
            pIntersect.y = lineseg.end.y;
         }
         else
         {
            // TODO: this could mean something's wrong, but maybe we should just log it or something?
            //assert( doesIntersect );
            continue;
         }
      }

      auto sprite = _renderData->GetSpriteById( lineseg.linedef->textureId );

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto rayLength = Geometry::Raycast( playerPosition, pIntersect, playerAngle );
      auto projectedWallHeight = ( ( _renderConfig->WallHeight / rayLength ) * _renderConfig->ProjectionPlaneDelta );

      _spritePosition.x = (float)i;
      _spritePosition.y = ( (float)_gameConfig->ScreenHeight - projectedWallHeight ) / 2.0f;
      sprite.setPosition( _spritePosition );

      _spriteTextureRect.left = (int)( sqrtf(
         powf( pIntersect.x - lineseg.linedef->start.x, 2 ) +
         powf( pIntersect.y - lineseg.linedef->start.y, 2 ) ) *
         _renderConfig->SpriteOffsetScalar );
      sprite.setTextureRect( _spriteTextureRect );

      _spriteVerticalScale.y = projectedWallHeight / (float)_gameConfig->ScreenHeight;
      sprite.setScale( _spriteVerticalScale );

      auto lightAdjustment = ( rayLength == 0.0f ) ? 0.0f : min( rayLength / _renderConfig->LightingScalar, 255.0f );
      auto lightValue = (Uint8)max( _renderConfig->LightingMinimum, (int)( 255.0f - lightAdjustment ) );
      sprite.setColor( Color( lightValue, lightValue, lightValue ) );

      _window->Draw( sprite );
   }
}

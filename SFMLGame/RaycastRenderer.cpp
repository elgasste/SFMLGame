#include <math.h>
#include <cassert>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "RaycastRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "Entity.h"
#include "SFMLWindow.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RaycastRenderer::RaycastRenderer( shared_ptr<GameConfig> gameConfig,
                                  shared_ptr<RenderConfig> renderConfig,
                                  shared_ptr<Entity> player,
                                  shared_ptr<SFMLWindow> window ) :
   _gameConfig( gameConfig ),
   _renderConfig( renderConfig ),
   _player( player ),
   _window( window )
{
   _renderColumns = (sf::Vertex*)malloc( sizeof( sf::Vertex ) * gameConfig->ScreenWidth * 2 );

   auto screenWidth = (float)gameConfig->ScreenWidth;
   auto screenHeight = (float)gameConfig->ScreenHeight;

   _ceilingRenderRect[0] = Vertex( Vector2f( 0, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[1] = Vertex( Vector2f( screenWidth, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[2] = Vertex( Vector2f( screenWidth, screenHeight / 2.0f ), Color::Black );
   _ceilingRenderRect[3] = Vertex( Vector2f( 0, screenHeight / 2.0f ), Color::Black );

   _floorRenderRect[0] = Vertex( Vector2f( 0, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[1] = Vertex( Vector2f( screenWidth, screenHeight / 2.0f ), Color::Black );
   _floorRenderRect[2] = Vertex( Vector2f( screenWidth, screenHeight ), Color( 128, 128, 128 ) );
   _floorRenderRect[3] = Vertex( Vector2f( 0, screenHeight ), Color( 128, 128, 128 ) );
}

RaycastRenderer::~RaycastRenderer()
{
   delete _renderColumns;
   _renderColumns = nullptr;
}

void RaycastRenderer::RenderCeilingAndFloor()
{
   _window->Draw( _ceilingRenderRect, 4, Quads );
   _window->Draw( _floorRenderRect, 4, Quads );
}

void RaycastRenderer::RenderLineseg( const Lineseg& lineseg,
                                     bool isLinedefLeftEdge,
                                     bool isLinedefRightEdge,
                                     float drawStartAngle,
                                     int startColumn,
                                     int endColumn )
{
   auto playerPosition = _player->GetPosition();
   auto playerAngle = _player->GetAngle();
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
            // if we're not at the edge of a lineseg, something's wrong
            assert( doesIntersect );
         }
      }

      auto rayLength = Geometry::Raycast( playerPosition, pIntersect, playerAngle );

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto projectedWallHeight = ( ( _renderConfig->WallHeight / rayLength ) * _renderConfig->ProjectionPlaneDelta );

      auto columnIndex = i * 2;

      auto color = ( ( i == startColumn && isLinedefLeftEdge ) || ( i == endColumn && isLinedefRightEdge ) )
                   ? Color::Black : lineseg.linedef->color;
      auto lightAdjustment = ( rayLength == 0.0f ) ? 0.0f : min( rayLength / _renderConfig->LightingScalar, 255.0f );
      color.r = (Uint8)max( 0, (int)( color.r - lightAdjustment ) );
      color.g = (Uint8)max( 0, (int)( color.g - lightAdjustment ) );
      color.b = (Uint8)max( 0, (int)( color.b - lightAdjustment ) );

      _renderColumns[columnIndex].color = color;
      _renderColumns[columnIndex + 1].color = color;
      _renderColumns[columnIndex].position.x = (float)i;
      _renderColumns[columnIndex].position.y = ( _gameConfig->ScreenHeight / 2.0f ) - ( projectedWallHeight / 2.0f );
      _renderColumns[columnIndex + 1].position.x = (float)i;
      _renderColumns[columnIndex + 1].position.y = ( _gameConfig->ScreenHeight / 2.0f ) + ( projectedWallHeight / 2.0f );

      _window->Draw( _renderColumns + columnIndex, 2, Lines );
   }
}

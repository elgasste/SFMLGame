#include <math.h>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "RaycastRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "GameData.h"
#include "RenderData.h"
#include "SFMLWindow.h"
#include "ColumnTracker.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RaycastRenderer::RaycastRenderer( shared_ptr<GameConfig> gameConfig,
                                  shared_ptr<GameData> gameData,
                                  shared_ptr<RenderConfig> renderConfig,
                                  shared_ptr<RenderData> renderData,
                                  shared_ptr<SFMLWindow> window,
                                  shared_ptr<ColumnTracker> columnTracker ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _renderData( renderData ),
   _window( window ),
   _columnTracker( columnTracker ),
   _leftFovAngle( 0 )
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
   _skyTextureScalar = (float)_renderData->GetTextureById( _renderConfig->SkySpriteId ).getSize().x / RAD_360;

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
   auto playerAngle = _gameData->GetPlayer()->GetAngle();
   _skyTextureRect.left = -(int)( playerAngle * _skyTextureScalar );

   auto& skySprite = _renderData->GetSpriteById( _renderConfig->SkySpriteId );
   skySprite.setPosition( _skyPosition );
   skySprite.setTextureRect( _skyTextureRect );
   _window->Draw( skySprite );

   _window->Draw( _floorRenderRect, 4, Quads );
}

void RaycastRenderer::Render()
{
   _columnTracker->Reset( 0, _gameConfig->ScreenWidth - 1 );

   auto player = _gameData->GetPlayer();
   _viewOrigin = player->GetPosition();
   _leftFovAngle = player->GetAngle() + ( _renderConfig->FovAngle / 2.0f );
   NORMALIZE_ANGLE( _leftFovAngle );

   RenderCeilingAndFloor();

   RenderNodeRecursive( _gameData->GetBspRootNode() );

   assert( _columnTracker->IsFullyTracked() );
}

void RaycastRenderer::RenderNodeRecursive( BspNode* node )
{
   if ( node == nullptr )
   {
      return;
   }

   if ( node->isLeaf )
   {
      RenderLeaf( node );
      return;
   }

   if ( Geometry::IsPointOnRightSide( _viewOrigin.x,
                                      _viewOrigin.y,
                                      node->linedef->start.x,
                                      node->linedef->start.y,
                                      node->linedef->end.x,
                                      node->linedef->end.y ) )
   {
      RenderNodeRecursive( node->rightChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         RenderNodeRecursive( node->leftChild );
      }
   }
   else
   {
      RenderNodeRecursive( node->leftChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         RenderNodeRecursive( node->rightChild );
      }
   }
}

void RaycastRenderer::RenderLeaf( BspNode* leaf )
{
   for ( const auto& lineseg : leaf->subsector->linesegs )
   {
      for ( int i = 0; i < _columnTracker->GetUntrackedRangeCount(); i++ )
      {
         auto rangeStart = _columnTracker->GetRangeStart( i );
         auto rangeEnd = _columnTracker->GetRangeEnd( i );

         auto undrawnLeftAngle = _leftFovAngle - ( _renderConfig->FovAngleIncrement * rangeStart );
         auto undrawnRightAngle = _leftFovAngle - ( _renderConfig->FovAngleIncrement * rangeEnd );

         NORMALIZE_ANGLE( undrawnLeftAngle );
         NORMALIZE_ANGLE( undrawnRightAngle );

         auto isLinesegStartInView = false;
         auto isLinesegEndInView = false;

         if ( !Geometry::IsLineInView( _viewOrigin,
                                       undrawnLeftAngle, undrawnRightAngle,
                                       lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y,
                                       isLinesegStartInView,
                                       isLinesegEndInView,
                                       true ) )
         {
            continue;
         }

         // calculate the range we want to draw based on whether the lineseg boundaries are in view
         auto leftDrawAngle = undrawnLeftAngle;
         auto rightDrawAngle = undrawnRightAngle;

         if ( isLinesegStartInView )
         {
            leftDrawAngle = Geometry::AngleToPoint( _viewOrigin, lineseg.start );
            NORMALIZE_ANGLE( leftDrawAngle );
         }

         if ( isLinesegEndInView )
         {
            rightDrawAngle = Geometry::AngleToPoint( _viewOrigin, lineseg.end );
            NORMALIZE_ANGLE( rightDrawAngle );
         }

         // reverse the calculation on the draw angles to find the pixel range that was drawn
         auto drawStartPixel = ( leftDrawAngle <= undrawnLeftAngle )
            ? rangeStart + (int)( ( undrawnLeftAngle - leftDrawAngle ) / _renderConfig->FovAngleIncrement )
            : rangeStart + (int)( ( undrawnLeftAngle + ( RAD_360 - leftDrawAngle ) ) / _renderConfig->FovAngleIncrement );
         auto drawEndPixel = ( rightDrawAngle >= undrawnRightAngle )
            ? rangeEnd - (int)( ( rightDrawAngle - undrawnRightAngle ) / _renderConfig->FovAngleIncrement )
            : rangeEnd - (int)( ( ( RAD_360 - undrawnRightAngle ) + rightDrawAngle ) / _renderConfig->FovAngleIncrement );

         RenderLineseg( lineseg, leftDrawAngle, drawStartPixel, drawEndPixel );

         auto prevRangeCount = _columnTracker->GetUntrackedRangeCount();
         _columnTracker->TrackRange( drawStartPixel, drawEndPixel );
         auto newRangeCount = _columnTracker->GetUntrackedRangeCount();

         if ( _columnTracker->IsFullyTracked() )
         {
            return;
         }
         else if ( newRangeCount > prevRangeCount )
         {
            // this range was split in the middle, skip to the next range
            i++;
         }
         else if ( newRangeCount < prevRangeCount )
         {
            // this entire range was removed, stay on the same index
            i--;
         }
      }
   }
}

void RaycastRenderer::RenderLineseg( const Lineseg& lineseg,
                                     float drawStartAngle,
                                     int startColumn,
                                     int endColumn )
{
   auto player = _gameData->GetPlayer();
   auto& playerPosition = player->GetPosition();
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

      auto& sprite = _renderData->GetSpriteById( lineseg.linedef->textureId );

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto rayLength = Geometry::Raycast( playerPosition, pIntersect, playerAngle, drawAngle );
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

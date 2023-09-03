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
   _pixelColumns = vector<PixelColumn>( gameConfig->ScreenWidth, PixelColumn() );

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

void RaycastRenderer::Render()
{
   _columnTracker->Reset( 0, _gameConfig->ScreenWidth - 1 );

   auto player = _gameData->GetPlayer();
   _viewOrigin = player->GetPosition();
   _leftFovAngle = player->GetAngle() + ( _renderConfig->FovAngle / 2.0f );
   NORMALIZE_ANGLE( _leftFovAngle );

   RenderCeilingAndFloor();
   CheckBspNodeRecursive( _gameData->GetBspRootNode() );
   RenderPixelColumns();

   assert( _columnTracker->IsFullyTracked() );
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

void RaycastRenderer::CheckBspNodeRecursive( BspNode* node )
{
   if ( node == nullptr )
   {
      return;
   }

   if ( node->isLeaf )
   {
      CheckBspLeaf( node );
      return;
   }

   if ( Geometry::IsPointOnRightSide( _viewOrigin.x, _viewOrigin.y, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y ) )
   {
      CheckBspNodeRecursive( node->rightChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         CheckBspNodeRecursive( node->leftChild );
      }
   }
   else
   {
      CheckBspNodeRecursive( node->leftChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         CheckBspNodeRecursive( node->rightChild );
      }
   }
}

void RaycastRenderer::CheckBspLeaf( BspNode* leaf )
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
         auto startPixel = ( leftDrawAngle <= undrawnLeftAngle )
            ? rangeStart + (int)( ( undrawnLeftAngle - leftDrawAngle ) / _renderConfig->FovAngleIncrement )
            : rangeStart + (int)( ( undrawnLeftAngle + ( RAD_360 - leftDrawAngle ) ) / _renderConfig->FovAngleIncrement );
         auto endPixel = ( rightDrawAngle >= undrawnRightAngle )
            ? rangeEnd - (int)( ( rightDrawAngle - undrawnRightAngle ) / _renderConfig->FovAngleIncrement )
            : rangeEnd - (int)( ( ( RAD_360 - undrawnRightAngle ) + rightDrawAngle ) / _renderConfig->FovAngleIncrement );

         SetPixelColumnRange( lineseg, leftDrawAngle, startPixel, endPixel );

         auto prevRangeCount = _columnTracker->GetUntrackedRangeCount();
         _columnTracker->TrackRange( startPixel, endPixel );
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

void RaycastRenderer::SetPixelColumnRange( const Lineseg& lineseg, float startAngle, int startPixel, int endPixel )
{
   auto player = _gameData->GetPlayer();
   auto& playerPosition = player->GetPosition();
   auto playerAngle = player->GetAngle();
   static Vector2f pIntersect;

   for ( int i = startPixel, j = 0; i <= endPixel; i++, j++ )
   {
      auto drawAngle = startAngle - ( j * _renderConfig->FovAngleIncrement );
      NORMALIZE_ANGLE( drawAngle );
      auto doesIntersect = Geometry::RayIntersectsLine( playerPosition, drawAngle, lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, &pIntersect );

      // this often happens around the edge of a lineseg, in which case we can just draw the edge
      if ( !doesIntersect )
      {
         if ( i == startPixel || i == startPixel + 1 )
         {
            pIntersect.x = lineseg.start.x;
            pIntersect.y = lineseg.start.y;
         }
         else if ( i == endPixel || i == endPixel - 1 )
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

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto rayLength = Geometry::Raycast( playerPosition, pIntersect, playerAngle, drawAngle );
      auto projectedWallHeight = ( ( _renderConfig->WallHeight / rayLength ) * _renderConfig->ProjectionPlaneDelta );
      auto lightAdjustment = ( rayLength == 0.0f ) ? 0.0f : min( rayLength / _renderConfig->LightingScalar, 255.0f );

      _pixelColumns[i].textureId = lineseg.linedef->textureId;
      _pixelColumns[i].yOffset = ( (float)_gameConfig->ScreenHeight - projectedWallHeight ) / 2.0f;
      _pixelColumns[i].textureOffsetX = (int)( sqrtf( powf( pIntersect.x - lineseg.linedef->start.x, 2 ) + powf( pIntersect.y - lineseg.linedef->start.y, 2 ) ) * _renderConfig->SpriteOffsetScalar );
      _pixelColumns[i].textureScaleY = projectedWallHeight / (float)_gameConfig->ScreenHeight;
      _pixelColumns[i].lightValue = (Uint8)max( _renderConfig->LightingMinimum, (int)( 255.0f - lightAdjustment ) );
   }
}

void RaycastRenderer::RenderPixelColumns()
{
   for ( int i = 0; i <= _gameConfig->ScreenWidth - 1; i++ )
   {
      auto& pixelColumn = _pixelColumns[i];
      auto& sprite = _renderData->GetSpriteById( pixelColumn.textureId );

      _spritePosition.x = (float)i;
      _spritePosition.y = pixelColumn.yOffset;
      sprite.setPosition( _spritePosition );

      _spriteTextureRect.left = pixelColumn.textureOffsetX;
      sprite.setTextureRect( _spriteTextureRect );

      _spriteVerticalScale.y = pixelColumn.textureScaleY;
      sprite.setScale( _spriteVerticalScale );

      sprite.setColor( Color( pixelColumn.lightValue, pixelColumn.lightValue, pixelColumn.lightValue ) );

      _window->Draw( sprite );
   }
}

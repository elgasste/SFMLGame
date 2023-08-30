#include <SFML/Graphics.hpp>

#include "TopDownRenderer.h"
#include "GameConfig.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "ColumnTracker.h"
#include "Sector.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

TopDownRenderer::TopDownRenderer( shared_ptr<GameConfig> gameConfig,
                                  shared_ptr<GameData> gameData,
                                  shared_ptr<RenderConfig> renderConfig,
                                  shared_ptr<SFMLWindow> window,
                                  shared_ptr<ColumnTracker> columnTracker ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _window( window ),
   _columnTracker( columnTracker ),
   _leftFovAngle( 0 )
{
   _linesegDrawer = VertexArray( LineStrip, 2 );
   _linesegDrawer[0].color = Color::White;
   _linesegDrawer[1].color = Color::White;

   _playerDrawer.setRadius( 3 );
   _playerDrawer.setOrigin( { 3, 3 } );
   _playerDrawer.setFillColor( Color::Red );

   _playerFovDrawer = VertexArray( LineStrip, 2 );
   _playerFovDrawer[0].color = Color::Green;
   _playerFovDrawer[1].color = Color::Green;
}

void TopDownRenderer::Render()
{
   _columnTracker->Reset( 0, _gameConfig->ScreenWidth - 1 );

   RenderFovRecursive( _gameData->GetBspRootNode() );

   RenderSectors();

   auto player = _gameData->GetPlayer();
   _viewOrigin = player->GetPosition();
   _leftFovAngle = player->GetAngle() + ( _renderConfig->FovAngle / 2.0f );

   _playerDrawer.setPosition( player->GetPosition() );
   _window->Draw( _playerDrawer );
}

void TopDownRenderer::RenderSectors()
{
   for ( auto& sector : *_gameData->GetSectors() )
   {
      for ( auto& linedef : sector.linedefs )
      {
         _linesegDrawer[0].position = linedef.start;
         _linesegDrawer[1].position = linedef.end;
         _window->Draw( _linesegDrawer );
      }
   }
}

void TopDownRenderer::RenderFovRecursive( BspNode* node )
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
      RenderFovRecursive( node->rightChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         RenderFovRecursive( node->leftChild );
      }
   }
   else
   {
      RenderFovRecursive( node->leftChild );

      if ( !_columnTracker->IsFullyTracked() )
      {
         RenderFovRecursive( node->rightChild );
      }
   }
}

void TopDownRenderer::RenderLeaf( BspNode* leaf )
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

void TopDownRenderer::RenderLineseg( const Lineseg& lineseg,
                                     float drawStartAngle,
                                     int startColumn,
                                     int endColumn )
{
   auto& playerPosition = _gameData->GetPlayer()->GetPosition();
   _playerFovDrawer[0].position = playerPosition;

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

      _playerFovDrawer[1].position = pIntersect;
      _window->Draw( _playerFovDrawer );
   }
}

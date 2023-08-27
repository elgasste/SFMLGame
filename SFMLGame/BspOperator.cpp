#include <cassert>

#include "BspOperator.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "Entity.h"
#include "RaycastRenderer.h"
#include "ColumnTracker.h"
#include "BspNode.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

BspOperator::BspOperator( shared_ptr<GameConfig> gameConfig,
                          shared_ptr<RenderConfig> renderConfig,
                          shared_ptr<RaycastRenderer> raycastRenderer,
                          shared_ptr<ColumnTracker> columnTracker,
                          BspNode* rootNode ) :
   _gameConfig( gameConfig ),
   _renderConfig( renderConfig ),
   _raycastRenderer( raycastRenderer ),
   _columnTracker( columnTracker ),
   _rootNode( rootNode ),
   _leftFovAngle( 0 )
{
}

BspOperator::~BspOperator()
{
   DeleteTreeRecursive( _rootNode );
}

void BspOperator::DeleteTreeRecursive( BspNode* node )
{
   if ( node == nullptr )
   {
      return;
   }

   if ( node->isLeaf )
   {
      delete node->subsector;
      node->subsector = nullptr;

      delete node;
      node = nullptr;
   }
   else
   {
      DeleteTreeRecursive( node->leftChild );
      DeleteTreeRecursive( node->rightChild );
   }
}

const Subsector& BspOperator::GetOccupyingSubsector( shared_ptr<Entity> entity ) const
{
   BspNode* node = _rootNode;
   auto& origin = entity->GetPosition();

   while ( !node->isLeaf )
   {
      node = Geometry::IsPointOnRightSide( origin.x, origin.y, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y )
         ? node->rightChild : node->leftChild;
   }

   return *( node->subsector );
}

void BspOperator::RenderWorld( shared_ptr<Entity> viewingEntity )
{
   _columnTracker->Reset( 0, _gameConfig->ScreenWidth - 1 );

   _viewOrigin = viewingEntity->GetPosition();
   _leftFovAngle = viewingEntity->GetAngle() + ( _renderConfig->FovAngle / 2.0f );
   NORMALIZE_ANGLE( _leftFovAngle );

   _raycastRenderer->RenderCeilingAndFloor();

   RenderNodeRecursive( _rootNode );

   assert( _columnTracker->IsFullyTracked() );
}

void BspOperator::RenderNodeRecursive( BspNode* node )
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

void BspOperator::RenderLeaf( BspNode* leaf )
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

         _raycastRenderer->RenderLineseg( lineseg, leftDrawAngle, drawStartPixel, drawEndPixel );

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

bool BspOperator::CheckWallCollision( float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const
{
   return CheckWallNodeCollisionRecursive( _rootNode, startX, startY, endX, endY, collidingLineseg );
}

bool BspOperator::CheckWallNodeCollisionRecursive( BspNode* node, float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const
{
   if ( node->isLeaf )
   {
      for ( auto& lineseg : node->subsector->linesegs )
      {
         // MUFFINS: send up the intersection point?
         if ( Geometry::LinesIntersect( startX, startY, endX, endY, lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, nullptr ) )
         {
            collidingLineseg = lineseg;
            return true;
         }
      }

      return false;
   }

   auto startIsOnRight = Geometry::IsPointOnRightSide( startX, startY, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y );
   auto endIsOnRight = Geometry::IsPointOnRightSide( endX, endY, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y );

   auto nextNode = startIsOnRight ? node->rightChild : node->leftChild;

   if ( startIsOnRight == endIsOnRight )
   {
      return CheckWallNodeCollisionRecursive( nextNode, startX, startY, endX, endY, collidingLineseg );
   }

   if ( CheckWallNodeCollisionRecursive( nextNode, startX, startY, endX, endY, collidingLineseg ) )
   {
      return true;
   }

   nextNode = startIsOnRight ? node->leftChild : node->rightChild;

   return CheckWallNodeCollisionRecursive( nextNode, startX, startY, endX, endY, collidingLineseg );
}

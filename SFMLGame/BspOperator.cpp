#include <cassert>

#include "BspOperator.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "Entity.h"
#include "RaycastRenderer.h"
#include "BspNode.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

BspOperator::BspOperator( shared_ptr<GameConfig> gameConfig,
                          shared_ptr<RenderConfig> renderConfig,
                          shared_ptr<RaycastRenderer> raycastRenderer,
                          BspNode* rootNode ) :
   _gameConfig( gameConfig ),
   _renderConfig( renderConfig ),
   _raycastRenderer( raycastRenderer ),
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
   if ( node != nullptr && node->isLeaf )
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

const Subsector& BspOperator::GetOccupyingSubsector( shared_ptr<Entity> entity )
{
   BspNode* node = _rootNode;
   auto origin = entity->GetPosition();

   while ( !node->isLeaf )
   {
      node = Geometry::IsPointOnRightSide( origin.x, origin.y, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y )
         ? node->rightChild : node->leftChild;
   }

   return *( node->subsector );
}

void BspOperator::RenderWorld( shared_ptr<Entity> viewingEntity )
{
   _undrawnRanges.clear();
   _undrawnRanges.push_back( { 0, _gameConfig->ScreenWidth - 1 } );

   _viewOrigin = viewingEntity->GetPosition();
   _leftFovAngle = viewingEntity->GetAngle() + ( _renderConfig->FovAngle / 2.0f );
   NORMALIZE_ANGLE( _leftFovAngle );

   _raycastRenderer->RenderCeilingAndFloor();

   RenderNodeRecursive( _rootNode );
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

      if ( !_undrawnRanges.empty() )
      {
         RenderNodeRecursive( node->leftChild );
      }
   }
   else
   {
      RenderNodeRecursive( node->leftChild );

      if ( !_undrawnRanges.empty() )
      {
         RenderNodeRecursive( node->rightChild );
      }
   }
}

void BspOperator::RenderLeaf( BspNode* leaf )
{
   for ( const auto& lineseg : leaf->subsector->linesegs )
   {
      for ( int i = 0; i < (int)_undrawnRanges.size(); i++ )
      {
         auto undrawnLeftAngle = _leftFovAngle - ( _renderConfig->FovAngleIncrement * _undrawnRanges[i].start );
         auto undrawnRightAngle = _leftFovAngle - ( _renderConfig->FovAngleIncrement * _undrawnRanges[i].end );

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
            ? _undrawnRanges[i].start + (int)( ( undrawnLeftAngle - leftDrawAngle ) / _renderConfig->FovAngleIncrement )
            : _undrawnRanges[i].start + (int)( ( undrawnLeftAngle + ( RAD_360 - leftDrawAngle ) ) / _renderConfig->FovAngleIncrement );
         auto drawEndPixel = ( rightDrawAngle >= undrawnRightAngle )
            ? _undrawnRanges[i].end - (int)( ( rightDrawAngle - undrawnRightAngle ) / _renderConfig->FovAngleIncrement )
            : _undrawnRanges[i].end - (int)( ( ( RAD_360 - undrawnRightAngle ) + rightDrawAngle ) / _renderConfig->FovAngleIncrement );

         _raycastRenderer->RenderLineseg( lineseg,
                                          lineseg.start == lineseg.linedef->start,
                                          lineseg.end == lineseg.linedef->end,
                                          leftDrawAngle,
                                          drawStartPixel,
                                          drawEndPixel );

         auto prevRangeCount = _undrawnRanges.size();
         MarkRangeAsDrawn( drawStartPixel, drawEndPixel );

         if ( _undrawnRanges.empty() )
         {
            return;
         }
         else if ( _undrawnRanges.size() > prevRangeCount )
         {
            // this range was split in the middle, skip to the next range
            i++;
         }
         else if ( _undrawnRanges.size() < prevRangeCount )
         {
            // this entire range was removed, stay on the same index
            i--;
         }
      }
   }
}

void BspOperator::MarkRangeAsDrawn( int start, int end )
{
   for ( int i = 0; i < (int)_undrawnRanges.size(); i++ )
   {
      auto& undrawnRange = _undrawnRanges[i];

      if ( end < undrawnRange.start )
      {
         // the list is ordered left to right, so we don't need to check further
         return;
      }
      else if ( start > undrawnRange.end )
      {
         continue;
      }

      if ( start > undrawnRange.start )
      {
         auto originalEnd = undrawnRange.end;
         undrawnRange.end = start - 1;

         if ( end < originalEnd )
         {
            _undrawnRanges.insert( _undrawnRanges.begin() + i + 1, { end + 1, originalEnd } );
         }
      }
      else
      {
         if ( end < undrawnRange.end )
         {
            undrawnRange.start = end + 1;
         }
         else
         {
            _undrawnRanges.erase( _undrawnRanges.begin() + i );
            i--;
         }
      }
   }
}

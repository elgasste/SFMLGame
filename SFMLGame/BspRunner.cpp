#include <cassert>

#include "BspRunner.h"
#include "GameConfig.h"
#include "Entity.h"
#include "BspNode.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

BspRunner::BspRunner( shared_ptr<GameConfig> config,
                      shared_ptr<Entity> player,
                      BspNode* rootNode ) :
   _config( config ),
   _player( player ),
   _rootNode( rootNode ),
   _leftFovAngle( 0 )
{
   _fovAngleIncrement = FovRange / config->ScreenWidth;

   // MUFFINS
   _treeDepth = 0;
   _maxTreeDepth = 0;
   _angleOfMaxTreeDepth = 0;
   _linesegsDrawn = 0;
   _maxLinesegsDrawn = 0;
   _angleOfMaxLinesegsDrawn = 0;
   _geometryChecks = 0;
   _maxGeometryChecks = 0;
   _angleOfMaxGeometryChecks = 0;
}

BspRunner::~BspRunner()
{
   DeleteTreeRecursive( _rootNode );
}

void BspRunner::DeleteTreeRecursive( BspNode* node )
{
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

void BspRunner::Run()
{
   // MUFFINS
   _treeDepth = 0;
   _linesegsDrawn = 0;
   _geometryChecks = 0;

   _undrawnRanges.clear();
   _undrawnRanges.push_back( { 0, _config->ScreenWidth - 1 } );

   _origin = _player->GetPosition();
   _leftFovAngle = _player->GetAngle() + RAD_30;
   NORMALIZE_ANGLE( _leftFovAngle );

   CheckNodeRecursive( _rootNode );

   // MUFFINS: maybe log this instead, at some point? Like have an "undrawn lines" count?
   assert( _undrawnRanges.empty() );

   // MUFFINS
   if ( _treeDepth > _maxTreeDepth )
   {
      _maxTreeDepth = _treeDepth;
      _angleOfMaxTreeDepth = _player->GetAngle();
   }
   if ( _linesegsDrawn > _maxLinesegsDrawn )
   {
      _maxLinesegsDrawn = _linesegsDrawn;
      _angleOfMaxLinesegsDrawn = _player->GetAngle();
   }
   if ( _geometryChecks > _maxGeometryChecks )
   {
      _maxGeometryChecks = _geometryChecks;
      _angleOfMaxGeometryChecks = _player->GetAngle();
   }
   _geometryCheckList.push_back( _geometryChecks );
}

void BspRunner::CheckNodeRecursive( BspNode* node )
{
   // MUFFINS
   _treeDepth++;

   if ( node->isLeaf )
   {
      CheckLeaf( node );
      return;
   }

   if ( Geometry::IsPointOnRightSide( _origin.x, _origin.y, node->linedef->start.x, node->linedef->start.y, node->linedef->end.x, node->linedef->end.y ) )
   {
      CheckNodeRecursive( node->rightChild );

      if ( !_undrawnRanges.empty() )
      {
         CheckNodeRecursive( node->leftChild );
      }
   }
   else
   {
      CheckNodeRecursive( node->leftChild );

      if ( !_undrawnRanges.empty() )
      {
         CheckNodeRecursive( node->rightChild );
      }
   }
}

void BspRunner::CheckLeaf( BspNode* leaf )
{
   for ( const auto& lineseg : leaf->subsector->linesegs )
   {
      for ( int i = 0; i < (int)_undrawnRanges.size(); i++ )
      {
         // MUFFINS
         _geometryChecks++;

         auto undrawnLeftAngle = _leftFovAngle - ( _fovAngleIncrement * _undrawnRanges[i].start );
         auto undrawnRightAngle = _leftFovAngle - ( _fovAngleIncrement * _undrawnRanges[i].end );

         NORMALIZE_ANGLE( undrawnLeftAngle );
         NORMALIZE_ANGLE( undrawnRightAngle );

         auto isLinesegStartInView = false;
         auto isLinesegEndInView = false;

         if ( !Geometry::IsLineInView( _origin,
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
            leftDrawAngle = Geometry::AngleToPoint( _origin, lineseg.start );
            NORMALIZE_ANGLE( leftDrawAngle );
         }

         if ( isLinesegEndInView )
         {
            rightDrawAngle = Geometry::AngleToPoint( _origin, lineseg.end );
            NORMALIZE_ANGLE( rightDrawAngle );
         }

         // MUFFINS: raycast from left to right over the range to draw
         _linesegsDrawn++;

         // reverse the calculation on the draw angles to find the pixel range that was drawn
         auto drawStartPixel = ( leftDrawAngle <= undrawnLeftAngle )
            ? _undrawnRanges[i].start + (int)( ( undrawnLeftAngle - leftDrawAngle ) / _fovAngleIncrement )
            : _undrawnRanges[i].start + (int)( ( undrawnLeftAngle + ( RAD_360 - leftDrawAngle ) ) / _fovAngleIncrement );
         auto drawEndPixel = ( rightDrawAngle >= undrawnRightAngle )
            ? _undrawnRanges[i].end - (int)( ( rightDrawAngle - undrawnRightAngle ) / _fovAngleIncrement )
            : _undrawnRanges[i].end - (int)( ( ( RAD_360 - undrawnRightAngle ) + rightDrawAngle ) / _fovAngleIncrement );

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

void BspRunner::MarkRangeAsDrawn( int start, int end )
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

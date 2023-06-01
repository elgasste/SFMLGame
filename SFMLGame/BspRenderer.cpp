#include <math.h>

#include "BspRenderer.h"
#include "GameConfig.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

BspRenderer::BspRenderer( shared_ptr<GameConfig> config, BspNode* rootNode ) :
   _rootNode( rootNode ),
   _entity( nullptr )
{
   _rayIncrement = ( RAD_30 * 2.0f ) / config->ScreenWidth;
}

BspRenderer::~BspRenderer()
{
   DeleteTreeRecursive( _rootNode );
}

void BspRenderer::DeleteTreeRecursive( BspNode* node )
{
   if ( node->IsLeaf )
   {
      delete node;
      node = nullptr;
   }
   else
   {
      DeleteTreeRecursive( node->LeftChild );
      DeleteTreeRecursive( node->RightChild );
   }
}

void BspRenderer::Traverse( std::shared_ptr<Entity> entity )
{
   _fovSegments.clear();
   _entity = entity;

   _fovSegments.push_back( Vector2f( _entity->GetAngle() + RAD_30, _entity->GetAngle() - RAD_30 ) );

   if ( _fovSegments[0].x >= RAD_360 )
   {
      _fovSegments[0].x -= RAD_360;
   }
   else if ( _fovSegments[0].y < 0 )
   {
      _fovSegments[0].y += RAD_360;
   }
   
   CheckNodeRecursive( _rootNode );
}

void BspRenderer::CheckNodeRecursive( BspNode* node )
{
   if ( node->IsLeaf )
   {
      CheckLeaf( node );
      return;
   }

   auto position = _entity->GetPosition();

   if ( Geometry::IsPointOnRightSide( position.x,
                                      position.y,
                                      node->linedef->start.x,
                                      node->linedef->start.y,
                                      node->linedef->end.x,
                                      node->linedef->end.y ) )
   {
      CheckNodeRecursive( node->RightChild );

      if ( !_fovSegments.empty() )
      {
         CheckNodeRecursive( node->LeftChild );
      }
   }
   else
   {
      CheckNodeRecursive( node->LeftChild );

      if ( !_fovSegments.empty() )
      {
         CheckNodeRecursive( node->RightChild );
      }
   }
}

void BspRenderer::CheckLeaf( BspNode* leaf )
{
   // used to store the ray's intersection point on the lineseg
   static Vector2f intersect;

   for ( const auto& lineseg : leaf->Linesegs )
   {
      for ( int i = 0; i < (int)_fovSegments.size(); i++ )
      {
         auto origin = _entity->GetPosition();

         if ( !Geometry::IsLinesegInView( origin, _fovSegments[i].x, _fovSegments[i].y, lineseg ) )
         {
            continue;
         }

         // find the angle to the left edge of the lineseg
         auto startAngle = atan2f( lineseg.start.y - origin.y, lineseg.start.x - origin.x );

         // if the angle is past the left edge of the FOV segment, use the segment's left edge.
         // these values are "normalized" in case the FOV is somewhere near 0 radians.
         if ( ( startAngle + RAD_360 ) > ( _fovSegments[i].x + RAD_360 ) )
         {
            startAngle = _fovSegments[i].x;
         }

         // raycast from left to right until we've either reached the right edge of the lineseg,
         // or the right edge of the FOV segment. These also have to be "normalized" (see above).
         auto rayAngle = startAngle;
         auto normalizedFovEdge = _fovSegments[i].y + RAD_360;

         while ( ( rayAngle + RAD_360 ) >= normalizedFovEdge )
         {
            if ( !Geometry::RayIntersectsLineseg( origin, rayAngle, lineseg, intersect ) )
            {
               break;
            }

            // MUFFINS: calculate how long the ray is, and tell the renderer to draw
            // this specific lineseg at this specific pixel column and at this specific
            // distance (we'll need to calculate these things)

            rayAngle -= _rayIncrement;

            if ( rayAngle < 0 )
            {
               rayAngle += RAD_360;
            }
         }

         i = CloseFovSegment( i, startAngle, rayAngle - _rayIncrement );
      }
   }
}

int BspRenderer::CloseFovSegment( int index, float startAngle, float endAngle )
{
   auto initialSegmentCount = _fovSegments.size();

   if ( startAngle < _fovSegments[index].x )
   {
      // the start angle is to the right of the FOV segment, insert a new segment
      _fovSegments.insert( _fovSegments.begin() + index + 1, Vector2f( endAngle - _rayIncrement, _fovSegments[index].y ) );
      _fovSegments[index].y = startAngle + _rayIncrement;
      index++;
   }
   else
   {
      // the start angle matches the left of the FOV segment, move the FOV's left edge
      _fovSegments[index].x = endAngle - _rayIncrement;
   }

   if ( _fovSegments[index].y > endAngle )
   {
      // the segment has been fully drawn
      _fovSegments.erase( _fovSegments.begin() + index );
   }

   // if we've added an extra segment, try that one next, otherwise continue as normal
   return _fovSegments.size() > initialSegmentCount ? index - 1 : index;
}

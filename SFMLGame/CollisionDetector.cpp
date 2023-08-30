#include "CollisionDetector.h"
#include "GameData.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

CollisionDetector::CollisionDetector( shared_ptr<GameData> gameData ) :
   _gameData( gameData )
{
}

bool CollisionDetector::CheckWallCollision( float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const
{
   return CheckWallNodeCollisionRecursive( _gameData->GetBspRootNode(), startX, startY, endX, endY, collidingLineseg);
}

bool CollisionDetector::CheckWallNodeCollisionRecursive( BspNode* node, float startX, float startY, float endX, float endY, Lineseg& collidingLineseg ) const
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

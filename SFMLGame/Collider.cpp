#include <limits>

#include "Collider.h"
#include "GameConfig.h"
#include "GameData.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Collider::Collider( shared_ptr<GameConfig> gameConfig,
                    shared_ptr<GameData> gameData ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _collisionDistanceCache( 0 )
{
}

void Collider::MoveEntity( shared_ptr<Entity> entity, Direction direction, float distance )
{
   entity->SetIsMoving( true );

   auto& position = entity->GetPosition();
   auto& hitBoxOffset = entity->GetHitBoxOffset();

   float startX = 0.0f;
   float startY = 0.0f;
   float deltaX = 0.0f;
   float deltaY = 0.0f;
   int hitBoxIncrementX = 0;
   int hitBoxIncrementY = 0;
   int blocks = 0;

   // check the hit box in increments, from left-to-right or top-to-bottom
   switch ( direction )
   {
      case Direction::Left:
         startX = position.x + hitBoxOffset.x;
         startY = position.y + hitBoxOffset.y;
         deltaX = -distance;
         hitBoxIncrementY = _gameConfig->HitBoxBlockSize;
         blocks = (int)entity->GetHitBoxSize().y / _gameConfig->HitBoxBlockSize;
         break;
      case Direction::Right:
         startX = position.x - hitBoxOffset.x;
         startY = position.y + hitBoxOffset.y;
         deltaX = distance;
         hitBoxIncrementY = _gameConfig->HitBoxBlockSize;
         blocks = (int)entity->GetHitBoxSize().y / _gameConfig->HitBoxBlockSize;
         break;
      case Direction::Up:
         startX = position.x + hitBoxOffset.x;
         startY = position.y + hitBoxOffset.y;
         deltaY = -distance;
         hitBoxIncrementX = _gameConfig->HitBoxBlockSize;
         blocks = (int)entity->GetHitBoxSize().x / _gameConfig->HitBoxBlockSize;
         break;
      case Direction::Down:
         startX = position.x + hitBoxOffset.x;
         startY = position.y - hitBoxOffset.y;
         deltaY = distance;
         hitBoxIncrementX = _gameConfig->HitBoxBlockSize;
         blocks = (int)entity->GetHitBoxSize().x / _gameConfig->HitBoxBlockSize;
         break;
   }

   float endX = startX;
   float endY = startY;
   static Vector2f collisionPoint;
   _collisionDistanceCache = numeric_limits<float>::max();
   bool collided = false;

   for ( int i = 0; i <= blocks; i++ )
   {
      endX = startX + deltaX;
      endY = startY + deltaY;

      if ( HitLinesegRecursive( _gameData->GetRootBspNode(), startX, startY, endX, endY, collisionPoint ) )
      {
         collided = true;
         auto collisionDistance = Geometry::DistanceToPoint( startX, startY, collisionPoint.x, collisionPoint.y );

         if ( collisionDistance < _collisionDistanceCache )
         {
            _collisionDistanceCache = collisionDistance;
         }
      }

      startX += hitBoxIncrementX;
      startY += hitBoxIncrementY;
   }

   // MUFFINS: try clipping from the nearest collision point
   if ( !collided )
   {
      entity->SetPosition( position.x + deltaX, position.y + deltaY );
   }
}

bool Collider::HitLinesegRecursive( BspNode* node, float startX, float startY, float endX, float endY, Vector2f& collisionPoint )
{
   if ( node == nullptr )
   {
      return false;
   }

   if ( node->isLeaf )
   {
      for ( const auto& lineseg : node->subSector->lineSegs )
      {
         if ( Geometry::LinesIntersect( startX, startY, endX, endY, lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, &collisionPoint ) )
         {
            return true;
         }
      }

      return false;
   }
   else
   {
      auto linedef = node->lineDef;
      auto isStartOnRight = Geometry::IsPointOnRightSide( startX, startY, linedef->start.x, linedef->start.y, linedef->end.x, linedef->end.y );
      auto isEndOnRight = Geometry::IsPointOnRightSide( endX, endY, linedef->start.x, linedef->start.y, linedef->end.x, linedef->end.y );

      auto hit = isStartOnRight
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint );

      if ( hit || ( isStartOnRight == isEndOnRight ) )
      {
         return hit;
      }

      return isEndOnRight
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint );
   }
}

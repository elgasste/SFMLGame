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
   _gameData( gameData )
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
   static Vector2f nearestCollisionPoint;
   float collisionAngle;
   float nearestCollisionAngle = 0.0f;
   float nearestCollisionStartX = 0.0f;
   float nearestCollisionStartY = 0.0f;
   float nearestCollisionDistance = numeric_limits<float>::max();
   bool collided = false;

   for ( int i = 0; i <= blocks; i++ )
   {
      endX = startX + deltaX;
      endY = startY + deltaY;

      if ( HitLinesegRecursive( _gameData->GetRootBspNode(), startX, startY, endX, endY, collisionPoint, collisionAngle ) )
      {
         collided = true;
         auto collisionDistance = Geometry::DistanceToPoint( startX, startY, collisionPoint.x, collisionPoint.y );

         if ( collisionDistance < nearestCollisionDistance )
         {
            nearestCollisionPoint.x = collisionPoint.x;
            nearestCollisionPoint.y = collisionPoint.y;
            nearestCollisionAngle = collisionAngle;
            nearestCollisionStartX = startX;
            nearestCollisionStartY = startY;
            nearestCollisionDistance = collisionDistance;
         }
      }

      startX += hitBoxIncrementX;
      startY += hitBoxIncrementY;
   }

   if ( collided )
   {
      // MUFFINS: do we need to add another test here to make sure we don't go out of bounds?
      // if the map tiles are bound to a 16-pixel boundary, it's probably not even possible...

      // clip the entity parallel to the lineseg
      auto parallelAngle = nearestCollisionAngle - RAD_90;
      Geometry::NormalizeAngle( parallelAngle );

      auto dx = cosf( parallelAngle ) * _gameConfig->LinesegClipDistance;
      auto dy = sinf( parallelAngle ) * _gameConfig->LinesegClipDistance;

      auto destinationX = ( nearestCollisionPoint.x + dx ) - ( nearestCollisionStartX - position.x );
      auto destinationY = ( nearestCollisionPoint.y - dy ) - ( nearestCollisionStartY - position.y );

      entity->SetPosition( destinationX, destinationY );
   }
   else
   {
      entity->SetPosition( position.x + deltaX, position.y + deltaY );
   }
}

bool Collider::HitLinesegRecursive( BspNode* node, float startX, float startY, float endX, float endY, Vector2f& collisionPoint, float& collisionAngle )
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
            collisionAngle = Geometry::AngleToPoint( lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y );
            Geometry::NormalizeAngle( collisionAngle );
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
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint, collisionAngle )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint, collisionAngle );

      if ( hit || ( isStartOnRight == isEndOnRight ) )
      {
         return hit;
      }

      return isEndOnRight
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint, collisionAngle )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint, collisionAngle );
   }
}

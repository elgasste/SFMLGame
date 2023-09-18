#include <limits>

#include "Collider.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameClock.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Collider::Collider( shared_ptr<GameConfig> gameConfig,
                    shared_ptr<GameData> gameData,
                    shared_ptr<GameClock> clock ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _clock( clock )
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
   float collisionLinesegAngle;
   float nearestCollisionLinesegAngle = 0.0f;
   float nearestCollisionStartX = 0.0f;
   float nearestCollisionStartY = 0.0f;
   float nearestCollisionEndX = 0.0f;
   float nearestCollisionEndY = 0.0f;
   float nearestCollisionDistance = numeric_limits<float>::max();
   bool collided = false;

   for ( int i = 0; i <= blocks; i++ )
   {
      endX = startX + deltaX;
      endY = startY + deltaY;

      if ( HitLinesegRecursive( _gameData->GetRootBspNode(), startX, startY, endX, endY, collisionPoint, collisionLinesegAngle ) )
      {
         collided = true;
         auto collisionDistance = Geometry::DistanceToPoint( startX, startY, collisionPoint.x, collisionPoint.y );

         if ( collisionDistance < nearestCollisionDistance )
         {
            nearestCollisionPoint.x = collisionPoint.x;
            nearestCollisionPoint.y = collisionPoint.y;
            nearestCollisionLinesegAngle = collisionLinesegAngle;
            nearestCollisionStartX = startX;
            nearestCollisionStartY = startY;
            nearestCollisionEndX = endX;
            nearestCollisionEndY = endY;
            nearestCollisionDistance = collisionDistance;
         }
      }

      startX += hitBoxIncrementX;
      startY += hitBoxIncrementY;
   }

   if ( collided )
   {
      // MUFFINS: this current only works when moving to the right, and colliding with surfaces that pointing down and to the left (or straight down).
      // I'm not sure if there's a "generic" way to handle this, other than to put a bunch of switch statements all over to
      // handle different directions. maybe there's an efficient way to do it?
      auto clippedDistance = Geometry::DistanceToPoint( nearestCollisionPoint.x, nearestCollisionPoint.y, nearestCollisionEndX, nearestCollisionEndY );

      nearestCollisionLinesegAngle += RAD_180;
      Geometry::NormalizeAngle( nearestCollisionLinesegAngle );

      // from 0 to 45 degrees, dy should go from zero to the full value of clippedDistance,
      // then from 45 to 90 degrees, it should go back down to zero.
      auto anglePercentage = 1.0f - ( nearestCollisionLinesegAngle / RAD_90 );
      auto dyFactor = sinf( anglePercentage * RAD_180 );
      auto dy = ( sinf( nearestCollisionLinesegAngle ) * clippedDistance ) * dyFactor;
      auto dx = dy / tanf( nearestCollisionLinesegAngle );

      auto destinationX = ( nearestCollisionPoint.x + dx ) - ( nearestCollisionStartX - position.x ) - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
      auto destinationY = ( nearestCollisionPoint.y - dy ) - ( nearestCollisionStartY - position.y ) - ( _gameConfig->LinesegClipDistance * anglePercentage );

      entity->SetPosition( destinationX, destinationY );
   }
   else
   {
      entity->SetPosition( position.x + deltaX, position.y + deltaY );
   }
}

bool Collider::HitLinesegRecursive( BspNode* node, float startX, float startY, float endX, float endY, Vector2f& collisionPoint, float& collisionLinesegAngle )
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
            collisionLinesegAngle = Geometry::AngleToPoint( lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y );
            Geometry::NormalizeAngle( collisionLinesegAngle );
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
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint, collisionLinesegAngle )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint, collisionLinesegAngle );

      if ( hit || ( isStartOnRight == isEndOnRight ) )
      {
         return hit;
      }

      return isEndOnRight
         ? HitLinesegRecursive( node->rightChild, startX, startY, endX, endY, collisionPoint, collisionLinesegAngle )
         : HitLinesegRecursive( node->leftChild, startX, startY, endX, endY, collisionPoint, collisionLinesegAngle );
   }
}

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

   // TODO: if we're clipping, we might need to do several more checks to make sure we haven't
   // collided with several more things. For now, let's let that go.
   if ( collided )
   {
      auto clippedDistance = Geometry::DistanceToPoint( nearestCollisionPoint.x, nearestCollisionPoint.y, nearestCollisionEndX, nearestCollisionEndY );

      // MUFFINS: I don't think I have the values quite right for lineseg clip distance scalars, it's tough to
      // calculate because every angle is either perfectly vertical/horizontal or perfectly diagonal.

      auto originOffsetX = nearestCollisionStartX - position.x;
      auto originOffsetY = nearestCollisionStartY - position.y;

      if ( nearestCollisionLinesegAngle <= RAD_90 ) // 0 to 90 degrees
      {
         auto linesegAngle = nearestCollisionLinesegAngle - 0.0f;
         Geometry::NormalizeAngle( linesegAngle );

         // from 0 to 45 degrees, dy should go from zero to the full value of clippedDistance,
         // then from 45 to 90 degrees, it should go back down to zero.
         auto anglePercentage = 1.0f - ( linesegAngle / RAD_90 );
         auto dyFactor = sinf( anglePercentage * RAD_180 );
         auto dy = ( sinf( linesegAngle ) * clippedDistance ) * dyFactor;
         auto dx = dy / tanf( linesegAngle );

         // this happens when linesegAngle is exactly zero
         if ( isnan( dx ) )
         {
            dx = 0.0f;
         }

         if ( direction == Direction::Left )
         {
            auto destinationX = ( nearestCollisionPoint.x - dx ) - originOffsetX + ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y + dy ) - originOffsetY + ( _gameConfig->LinesegClipDistance * anglePercentage );
            entity->SetPosition( destinationX, destinationY );
         }
         else // Direction::Up
         {
            auto destinationX = ( nearestCollisionPoint.x + dx ) - originOffsetX + ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y - dy ) - originOffsetY + ( _gameConfig->LinesegClipDistance * anglePercentage );
            entity->SetPosition( destinationX, destinationY );
         }
      }
      else if ( nearestCollisionLinesegAngle <= RAD_180 ) // 90 to 180 degrees
      {
         auto linesegAngle = nearestCollisionLinesegAngle - RAD_90;
         Geometry::NormalizeAngle( linesegAngle );

         // from 0 to 45 degrees, dy should go from zero to the full value of clippedDistance,
         // then from 45 to 90 degrees, it should go back down to zero.
         auto anglePercentage = 1.0f - ( linesegAngle / RAD_90 );
         auto dyFactor = sinf( anglePercentage * RAD_180 );
         auto dy = ( sinf( linesegAngle ) * clippedDistance ) * dyFactor;
         auto dx = dy / tanf( linesegAngle );

         if ( direction == Direction::Left )
         {
            auto destinationX = ( nearestCollisionPoint.x - dx ) - originOffsetX + ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y - dy ) - originOffsetY - ( _gameConfig->LinesegClipDistance * anglePercentage );
            entity->SetPosition( destinationX, destinationY );
         }
         else // Direction::Down
         {
            auto destinationX = ( nearestCollisionPoint.x + dx ) - originOffsetX + ( _gameConfig->LinesegClipDistance * anglePercentage );
            auto destinationY = ( nearestCollisionPoint.y + dy ) - originOffsetY - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            entity->SetPosition( destinationX, destinationY );
         }
      }
      else if ( nearestCollisionLinesegAngle <= RAD_270 ) // 180 to 270 degrees
      {
         auto linesegAngle = nearestCollisionLinesegAngle - RAD_180;
         Geometry::NormalizeAngle( linesegAngle );

         // from 0 to 45 degrees, dy should go from zero to the full value of clippedDistance,
         // then from 45 to 90 degrees, it should go back down to zero.
         auto anglePercentage = 1.0f - ( linesegAngle / RAD_90 );
         auto dyFactor = sinf( anglePercentage * RAD_180 );
         auto dy = ( sinf( linesegAngle ) * clippedDistance ) * dyFactor;
         auto dx = dy / tanf( linesegAngle );

         if ( direction == Direction::Right )
         {
            auto destinationX = ( nearestCollisionPoint.x + dx ) - originOffsetX - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y - dy ) - originOffsetY - ( _gameConfig->LinesegClipDistance * anglePercentage );
            entity->SetPosition( destinationX, destinationY );
         }
         else // Direction::Down
         {
            auto destinationX = ( nearestCollisionPoint.x - dx ) - originOffsetX - ( _gameConfig->LinesegClipDistance * anglePercentage );
            auto destinationY = ( nearestCollisionPoint.y + dy ) - originOffsetY - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            entity->SetPosition( destinationX, destinationY );
         }
      }
      else if ( nearestCollisionLinesegAngle <= RAD_360 ) // 270 to 360 degrees
      {
         auto linesegAngle = nearestCollisionLinesegAngle - RAD_270;
         Geometry::NormalizeAngle( linesegAngle );

         // from 0 to 45 degrees, dy should go from zero to the full value of clippedDistance,
         // then from 45 to 90 degrees, it should go back down to zero.
         auto anglePercentage = 1.0f - ( linesegAngle / RAD_90 );
         auto dyFactor = sinf( anglePercentage * RAD_180 );
         auto dy = ( sinf( linesegAngle ) * clippedDistance ) * dyFactor;
         auto dx = dy / tanf( linesegAngle );

         if ( direction == Direction::Right )
         {
            auto destinationX = ( nearestCollisionPoint.x + dx ) - originOffsetX - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y + dy ) - originOffsetY + ( _gameConfig->LinesegClipDistance * anglePercentage );
            entity->SetPosition( destinationX, destinationY );
         }
         else // Direction::Up
         {
            auto destinationX = ( nearestCollisionPoint.x - dx ) - originOffsetX - ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            auto destinationY = ( nearestCollisionPoint.y - dy ) - originOffsetY + ( _gameConfig->LinesegClipDistance * ( 1.0f - anglePercentage ) );
            entity->SetPosition( destinationX, destinationY );
         }
      }
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

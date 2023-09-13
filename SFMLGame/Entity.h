#pragma once

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   const sf::Vector2f& GetPosition() const { return _position; }
   const sf::Vector2f& GetHitBoxSize() const { return _hitBoxSize; }
   const sf::Vector2f& GetHitBoxOffset() const { return _hitBoxOffset; }
   Direction GetDirection() const { return _direction; }
   bool IsMoving() const { return _isMoving; }

   void SetPosition( float x, float y );
   void SetHitBoxSize( float width, float height );
   void SetHitBoxOffset( float x, float y );
   void SetDirection( Direction direction ) { _direction = direction; }
   void SetIsMoving( bool isMoving ) { _isMoving = isMoving; }

private:
   sf::Vector2f _position;
   sf::Vector2f _hitBoxSize;
   sf::Vector2f _hitBoxOffset;
   Direction _direction;
   bool _isMoving;
};

NAMESPACE_END

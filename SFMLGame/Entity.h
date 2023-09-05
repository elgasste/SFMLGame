#pragma once

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   const sf::FloatRect& GetHitBox() const { return _hitBox; }
   const sf::Vector2f& GetPosition() const { return _position; }
   Direction GetDirection() const { return _direction; }
   bool IsMoving() const { return _isMoving; }

   void SetHitBoxDimensions( float width, float height );
   void SetPosition( float x, float y );
   void SetDirection( Direction direction ) { _direction = direction; }
   void SetIsMoving( bool isMoving ) { _isMoving = isMoving; }

private:
   sf::FloatRect _hitBox;
   sf::Vector2f _position;
   Direction _direction;
   bool _isMoving;
};

NAMESPACE_END

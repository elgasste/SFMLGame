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
   float GetVelocity() const { return _velocity; }

   void SetHitBoxDimensions( float width, float height );
   void SetPosition( float x, float y );
   void SetDirection( Direction direction ) { _direction = direction; }
   void SetVelocity( float velocity ) { _velocity = velocity; }

private:
   sf::FloatRect _hitBox;
   sf::Vector2f _position;
   Direction _direction;
   float _velocity;
};

NAMESPACE_END

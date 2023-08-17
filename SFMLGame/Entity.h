#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   const sf::FloatRect& GetHitBox() const { return _hitBox; }
   const sf::Vector2f& GetPosition() const { return _position; }
   float GetAngle() const { return _angle; }
   float GetVelocity() const { return _velocity; }

   void SetHitBoxDimensions( float width, float height );
   void SetPosition( float x, float y );
   void SetAngle( float angle ) { _angle = angle; }
   void SetVelocity( float velocity ) { _velocity = velocity; }

private:
   sf::FloatRect _hitBox;
   sf::Vector2f _position;
   float _angle;
   float _velocity;
};

NAMESPACE_END

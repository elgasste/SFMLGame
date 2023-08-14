#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   const sf::Vector2f& GetPosition() const { return _position; }
   const sf::FloatRect& GetHitBox() const { return _hitBox; }
   float GetAngle() { return _angle; }
   float GetForwardVelocity() { return _forwardVelocity; }
   float GetSidewaysVelocity() { return _sidewaysVelocity; }

   void SetPosition( float x, float y );
   void SetHitBox( float x, float y, float width, float height );
   void SetAngle( float angle );
   void SetForwardVelocity( float velocity ) { _forwardVelocity = velocity; }
   void SetSidewaysVelocity( float velocity ) { _sidewaysVelocity = velocity; }

   float GetHitBoxCornerRayLength() { return _hitBoxCornerRayLength; }
   float GetHitBoxFrontCornerAngle() { return _hitBoxFrontCornerAngle; }
   float GetHitBoxRearCornerAngle() { return _hitBoxRearCornerAngle; }

private:
   sf::Vector2f _position;
   sf::FloatRect _hitBox;
   float _angle;
   float _forwardVelocity;
   float _sidewaysVelocity;

   float _hitBoxCornerRayLength;
   float _hitBoxFrontCornerAngle;
   float _hitBoxRearCornerAngle;
};

NAMESPACE_END

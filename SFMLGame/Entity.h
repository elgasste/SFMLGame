#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   sf::Vector2f GetPosition() { return _position; }
   void SetPosition( sf::Vector2f position ) { _position = position; }

   float GetRadius() { return _radius; }
   float GetAngle() { return _angle; }
   float GetForwardVelocity() { return _forwardVelocity; }
   float GetSidewaysVelocity() { return _sidewaysVelocity; }

   void SetRadius( float radius ) { _radius = radius; }
   void SetAngle( float angle );
   void SetForwardVelocity( float velocity ) { _forwardVelocity = velocity; }
   void SetSidewaysVelocity( float velocity ) { _sidewaysVelocity = velocity; }

private:
   sf::Vector2f _position;
   float _radius;
   float _angle;
   float _forwardVelocity;
   float _sidewaysVelocity;
};

NAMESPACE_END

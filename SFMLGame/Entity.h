#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class Entity
{
public:
   Entity();

   const sf::Vector2f& GetPosition() const { return _position; }
   float GetAngle() { return _angle; }
   float GetForwardVelocity() { return _forwardVelocity; }
   float GetSidewaysVelocity() { return _sidewaysVelocity; }

   void SetPosition( float x, float y );
   void SetAngle( float angle );
   void SetForwardVelocity( float velocity ) { _forwardVelocity = velocity; }
   void SetSidewaysVelocity( float velocity ) { _sidewaysVelocity = velocity; }

private:
   sf::Vector2f _position;
   float _angle;
   float _forwardVelocity;
   float _sidewaysVelocity;
};

NAMESPACE_END

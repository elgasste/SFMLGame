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

   float GetAngle() { return _angle; }
   void SetAngle( float angle ) { _angle = angle; }

private:
   sf::Vector2f _position;
   float _angle;
};

NAMESPACE_END

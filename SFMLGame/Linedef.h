#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Common.h"

NAMESPACE_BEGIN

struct Linedef
{
   sf::Vector2f start;
   sf::Vector2f end;
   sf::Color color;
};

NAMESPACE_END

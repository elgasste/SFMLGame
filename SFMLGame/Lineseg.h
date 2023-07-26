#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "Linedef.h"

NAMESPACE_BEGIN

struct Lineseg
{
   Linedef* linedef;

   sf::Vector2f start;
   sf::Vector2f end;
};

NAMESPACE_END

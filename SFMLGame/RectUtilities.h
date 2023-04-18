#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class RectUtilities
{
public:
   static bool ClampRectToBounds( sf::Vector2f& position, const sf::FloatRect& rect, const sf::FloatRect& bounds );
};

NAMESPACE_END

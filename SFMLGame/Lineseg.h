#pragma once

#include "Common.h"
#include "LineDef.h"

NAMESPACE_BEGIN

struct LineSeg
{
   LineDef* lineDef;
   sf::Vector2f start;
   sf::Vector2f end;
};

NAMESPACE_END

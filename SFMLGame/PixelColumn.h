#pragma once

#include "Common.h"

NAMESPACE_BEGIN

struct PixelColumn
{
   float yOffset;
   int textureId;
   int textureOffsetX;
   float textureScaleY;
   sf::Uint8 lightValue;
};

NAMESPACE_END

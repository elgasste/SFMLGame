#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;

class RenderConfig
{
public:
   RenderConfig( std::shared_ptr<GameConfig> gameConfig );

public:
   float FovAngle;
   float FovAngleIncrement;

   float WallHeight;
   float ProjectionPlaneDelta;
   float LightingScalar;
};

NAMESPACE_END

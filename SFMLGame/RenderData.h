#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameClock;
class Entity;
class EntitySprite;

class RenderData
{
public:
   RenderData( std::shared_ptr<GameClock> clock,
               std::shared_ptr<Entity> player );

public:
   std::shared_ptr<EntitySprite> PlayerSprite;
};

NAMESPACE_END

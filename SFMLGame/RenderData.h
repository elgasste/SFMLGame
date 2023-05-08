#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameClock;
class Entity;
class Actor;
class EntitySprite;

class RenderData
{
public:
   RenderData( std::shared_ptr<GameClock> clock,
               std::shared_ptr<Entity> player,
               std::shared_ptr<Entity> npc );

public:
   std::shared_ptr<EntitySprite> PlayerSprite;
   std::shared_ptr<EntitySprite> NpcSprite;
};

NAMESPACE_END

#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameClock;
class Actor;
class ActorSprite;

class RenderData
{
public:
   RenderData( std::shared_ptr<GameClock> clock,
               std::shared_ptr<Actor> player );

public:
   std::shared_ptr<ActorSprite> PlayerSprite;
};

NAMESPACE_END

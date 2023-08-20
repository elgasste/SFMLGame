#pragma once

#include "Common.h"
#include "GameEventType.h"

NAMESPACE_BEGIN

class IGameEventArgs;

struct GameEvent
{
   GameEventType type;
   std::shared_ptr<IGameEventArgs> args;
};

NAMESPACE_END

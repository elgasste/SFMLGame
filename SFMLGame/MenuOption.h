#pragma once

#include "Common.h"
#include "GameEvent.h"

NAMESPACE_BEGIN

class IGameEventArgs;

struct MenuOption
{
   std::string menuText;
   GameEventType eventType = (GameEventType)0;
   std::shared_ptr<IGameEventArgs> eventArgs;
};

NAMESPACE_END

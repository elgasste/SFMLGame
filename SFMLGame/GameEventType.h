#pragma once

#include "Common.h"

NAMESPACE_BEGIN

enum class GameEventType
{
   Quit = 0,
   ChangeGameState,
   TurnBall,
   PushBall
};

NAMESPACE_END

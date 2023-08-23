#pragma once

#include "Common.h"

NAMESPACE_BEGIN

enum class GameEventType
{
   Quit = 0,
   ExitToTitle,
   OpenMenu,
   CloseMenu,
   StartGame,
   TurnBall,
   PushBall
};

NAMESPACE_END

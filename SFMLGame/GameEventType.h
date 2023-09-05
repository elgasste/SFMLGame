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
   MovePlayer
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

struct MovePlayerCommandArgs
{
   Direction direction = (Direction)0;
   float velocity = 0;
};

NAMESPACE_END

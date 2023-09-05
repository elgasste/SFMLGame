#pragma once

#include "Common.h"
#include "IGameEventArgs.h"
#include "Direction.h"

NAMESPACE_BEGIN

class MovePlayerArgs : public IGameEventArgs
{
public:
   MovePlayerArgs( Direction direction ) { _direction = direction; }

   Direction GetDirection() { return _direction; }

private:
   Direction _direction;
};

NAMESPACE_END

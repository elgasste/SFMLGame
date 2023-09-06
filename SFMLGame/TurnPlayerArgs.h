#pragma once

#include "Common.h"
#include "IGameEventArgs.h"
#include "Direction.h"

NAMESPACE_BEGIN

class TurnPlayerArgs : public IGameEventArgs
{
public:
   TurnPlayerArgs( Direction direction ) { _direction = direction; }

   Direction GetDirection() { return _direction; }

private:
   Direction _direction;
};

NAMESPACE_END

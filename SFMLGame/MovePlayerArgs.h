#pragma once

#include "Common.h"
#include "IGameEventArgs.h"
#include "Direction.h"

NAMESPACE_BEGIN

class MovePlayerArgs : public IGameEventArgs
{
public:
   MovePlayerArgs( Direction direction, float velocity )
   {
      _direction = direction;
      _velocity = velocity;
   }

   Direction GetDirection() { return _direction; }
   float GetVelocity() { return _velocity; }

private:
   Direction _direction;
   float _velocity;
};

NAMESPACE_END

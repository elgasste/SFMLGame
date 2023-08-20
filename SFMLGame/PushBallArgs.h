#pragma once

#include "Common.h"
#include "IGameEventArgs.h"

NAMESPACE_BEGIN

class PushBallArgs : public IGameEventArgs
{
public:
   PushBallArgs( float increment ) { _increment = increment; }

   float GetIncrement() { return _increment; }

private:
   float _increment;
};

NAMESPACE_END

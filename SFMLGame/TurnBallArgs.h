#pragma once

#include "Common.h"
#include "IGameEventArgs.h"

NAMESPACE_BEGIN

class TurnBallArgs : public IGameEventArgs
{
public:
   TurnBallArgs( float newAngle ) { _newAngle = newAngle; }

   float GetNewAngle() { return _newAngle; }

private:
   float _newAngle;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameStateController
{
public:
   GameStateController();

   GameState GetState() const { return _state; }
   void SetState( GameState state ) { _state = state; }

private:
   GameState _state;
};

NAMESPACE_END

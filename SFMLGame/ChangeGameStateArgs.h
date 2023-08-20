#pragma once

#include "Common.h"
#include "IGameEventArgs.h"
#include "GameState.h"

NAMESPACE_BEGIN

class ChangeGameStateArgs : public IGameEventArgs
{
public:
   ChangeGameStateArgs( GameState newState ) { _newState = newState; }

   GameState GetNewState() { return _newState; }

private:
   GameState _newState;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameData
{
public:
   GameData();

   GameState GetGameState() const { return _gameState; }

   void SetGameState( GameState state ) { _gameState = state; }

private:
   GameState _gameState;
};

NAMESPACE_END

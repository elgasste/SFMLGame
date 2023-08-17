#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<Entity> ball );

   GameState GetGameState() const { return _gameState; }
   std::shared_ptr<Entity> GetBall() const { return _ball; }

   void SetGameState( GameState state ) { _gameState = state; }

private:
   GameState _gameState;
   std::shared_ptr<Entity> _ball;
};

NAMESPACE_END

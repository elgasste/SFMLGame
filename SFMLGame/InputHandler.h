#pragma once

#include "Common.h"
#include "GameStateTracker.h"

NAMESPACE_BEGIN

class GameConfig;
class InputStateController;
class IGameStateInputHandler;

class InputHandler
{
public:
   InputHandler( std::shared_ptr<GameConfig> gameConfig,
                 std::shared_ptr<InputStateController> inputReader,
                 std::shared_ptr<GameStateTracker> gameStateTracker );

   void AddStateInputHandler( GameState state, std::shared_ptr<IGameStateInputHandler> handler );
   void HandleInput();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<InputStateController> _inputReader;
   std::shared_ptr<GameStateTracker> _gameStateTracker;

   std::map<GameState, std::shared_ptr<IGameStateInputHandler>> _stateInputHandlerMap;
};

NAMESPACE_END

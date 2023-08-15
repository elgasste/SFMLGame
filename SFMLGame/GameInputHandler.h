#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameConfig;
class IInputReader;
class GameStateController;
class IGameStateInputHandler;

class GameInputHandler
{
public:
   GameInputHandler( std::shared_ptr<GameConfig> gameConfig,
                     std::shared_ptr<IInputReader> inputReader,
                     std::shared_ptr<GameStateController> stateController );

   void AddStateInputHandler( GameState state, std::shared_ptr<IGameStateInputHandler> handler );
   void HandleInput();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<GameStateController> _stateController;

   std::map<GameState, std::shared_ptr<IGameStateInputHandler>> _stateInputHandlerMap;
};

NAMESPACE_END

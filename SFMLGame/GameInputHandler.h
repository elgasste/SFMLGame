#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class InputReader;
class IGameStateInputHandler;

class GameInputHandler
{
public:
   GameInputHandler( std::shared_ptr<GameConfig> gameConfig,
                     std::shared_ptr<GameData> gameData,
                     std::shared_ptr<InputReader> inputReader );

   void AddStateInputHandler( GameState state, std::shared_ptr<IGameStateInputHandler> handler );
   void HandleInput();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<InputReader> _inputReader;

   std::map<GameState, std::shared_ptr<IGameStateInputHandler>> _stateInputHandlerMap;
};

NAMESPACE_END

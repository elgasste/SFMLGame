#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameConfig;
class IInputReader;
class EventAggregator;
class IGameStateInputHandler;
class GameStateProvider;

class GameInputHandler
{
public:
   GameInputHandler( std::shared_ptr<GameConfig> config,
                     std::shared_ptr<IInputReader> inputReader,
                     std::shared_ptr<EventAggregator> eventAggregator,
                     std::map<GameState, std::shared_ptr<IGameStateInputHandler>> gameStateInputHandlers,
                     std::shared_ptr<GameStateProvider> gameStateProvider );

   void HandleInput() const;

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::map<GameState, std::shared_ptr<IGameStateInputHandler>> _gameStateInputHandlers;
   std::shared_ptr<GameStateProvider> _gameStateProvider;
};

NAMESPACE_END

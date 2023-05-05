#pragma once

#include "Common.h"
#include "ICommandExecutor.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class GameStateProvider;
class EventAggregator;
class CommandAggregator;
class GameInputHandler;
class Arena;

class GameLogic : public ICommandExecutor
{
public:
   GameLogic( std::shared_ptr<GameConfig> config,
              std::shared_ptr<GameData> gameData,
              std::shared_ptr<GameStateProvider> gameStateProvider,
              std::shared_ptr<EventAggregator> eventAggregator,
              std::shared_ptr<CommandAggregator> commandAggregator,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<Arena> arena );

   void Start();
   void Tick();

   // ICommandExecutor
   void ExecuteCommand( GameCommand command, void* arg ) override;

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameStateProvider> _gameStateProvider;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<Arena> _arena;
};

NAMESPACE_END

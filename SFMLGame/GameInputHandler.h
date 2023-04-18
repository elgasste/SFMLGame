#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class IInputReader;
class EventAggregator;
class ArenaInputHandler;

class GameInputHandler
{
public:
   GameInputHandler( std::shared_ptr<GameConfig> config,
                     std::shared_ptr<IInputReader> inputReader,
                     std::shared_ptr<EventAggregator> eventAggregator,
                     std::shared_ptr<ArenaInputHandler> arenaInputHandler );

   void HandleInput() const;

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<ArenaInputHandler> _arenaInputHandler;
};

NAMESPACE_END

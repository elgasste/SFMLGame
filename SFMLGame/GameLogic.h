#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class EventAggregator;
class GameInputHandler;
class Arena;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameConfig> config,
              std::shared_ptr<EventAggregator> eventAggregator,
              std::shared_ptr<GameInputHandler> inputHandler,
              std::shared_ptr<Arena> arena );

   void Tick();

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<GameInputHandler> _inputHandler;
   std::shared_ptr<Arena> _arena;
};

NAMESPACE_END

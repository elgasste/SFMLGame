#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class EventAggregator;
class IInputReader;

class GameLogic
{
public:
   GameLogic( std::shared_ptr<GameConfig> config,
              std::shared_ptr<EventAggregator> eventAggregator,
              std::shared_ptr<IInputReader> inputReader );

   void Tick();

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<EventAggregator> _eventAggregator;
   std::shared_ptr<IInputReader> _inputReader;
};

NAMESPACE_END

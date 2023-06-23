#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class IInputReader;
class EventAggregator;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<IInputReader> inputReader,
                             std::shared_ptr<EventAggregator> eventAggregator );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<IInputReader> _inputReader;
   std::shared_ptr<EventAggregator> _eventAggregator;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class CommandAggregator;
class IInputReader;

class PlayingStateInputHandler : public IGameStateInputHandler
{
public:
   PlayingStateInputHandler( std::shared_ptr<CommandAggregator> commandAggregator,
                             std::shared_ptr<IInputReader> inputReader );

   void HandleInput() override;

private:
   std::shared_ptr<CommandAggregator> _commandAggregator;
   std::shared_ptr<IInputReader> _inputReader;
};

NAMESPACE_END

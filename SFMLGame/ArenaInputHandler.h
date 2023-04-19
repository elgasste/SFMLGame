#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class CommandAggregator;
class IInputReader;

class ArenaInputHandler
{
public:
   ArenaInputHandler( std::shared_ptr<CommandAggregator> commandAggregator,
                      std::shared_ptr<IInputReader> inputReader );

   void HandleInput() const;

private:
   std::shared_ptr<CommandAggregator> _commandAggregator;
   std::shared_ptr<IInputReader> _inputReader;
};

NAMESPACE_END

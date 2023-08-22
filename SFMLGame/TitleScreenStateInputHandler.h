#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class EventQueue;

class TitleScreenStateInputHandler : public IGameStateInputHandler
{
public:
   TitleScreenStateInputHandler( std::shared_ptr<InputReader> inputReader,
                                 std::shared_ptr<EventQueue> eventQueue );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<EventQueue> _eventQueue;
};

NAMESPACE_END

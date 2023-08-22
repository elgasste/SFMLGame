#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputReader;
class EventQueue;
class TitleMenu;

class TitleMenuStateInputHandler : public IGameStateInputHandler
{
public:
   TitleMenuStateInputHandler( std::shared_ptr<InputReader> inputReader,
                               std::shared_ptr<EventQueue> eventQueue,
                               std::shared_ptr<TitleMenu> menu );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputReader> _inputReader;
   std::shared_ptr<EventQueue> _eventQueue;
   std::shared_ptr<TitleMenu> _menu;
};

NAMESPACE_END

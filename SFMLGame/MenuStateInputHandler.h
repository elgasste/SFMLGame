#pragma once

#include "Common.h"
#include "IGameStateInputHandler.h"

NAMESPACE_BEGIN

class InputStateController;
class EventQueue;
class Menu;

class MenuStateInputHandler : public IGameStateInputHandler
{
public:
   MenuStateInputHandler( std::shared_ptr<InputStateController> inputReader,
                          std::shared_ptr<EventQueue> eventQueue,
                          std::shared_ptr<Menu> menu );

   // IGameStateInputHandler
   void HandleInput() override;

private:
   std::shared_ptr<InputStateController> _inputReader;
   std::shared_ptr<EventQueue> _eventQueue;
   std::shared_ptr<Menu> _menu;
};

NAMESPACE_END

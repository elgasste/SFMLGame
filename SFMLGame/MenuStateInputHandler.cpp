#include "MenuStateInputHandler.h"
#include "InputStateController.h"
#include "EventQueue.h"
#include "Menu.h"

using namespace NAMESPACE;
using namespace std;

MenuStateInputHandler::MenuStateInputHandler( shared_ptr<InputStateController> inputStateController,
                                              shared_ptr<EventQueue> eventQueue,
                                              shared_ptr<Menu> menu ) :
   _inputStateController( inputStateController ),
   _eventQueue( eventQueue ),
   _menu( menu )
{
}

void MenuStateInputHandler::HandleInput()
{
   if ( _inputStateController->WasButtonPressed( Button::Back ) )
   {
      _eventQueue->Push( GameEventType::CloseMenu );
   }
   else if ( _inputStateController->WasButtonPressed( Button::Up ) )
   {
      _menu->ScrollUp();
   }
   else if ( _inputStateController->WasButtonPressed( Button::Down ) )
   {
      _menu->ScrollDown();
   }
   else if ( _inputStateController->WasButtonPressed( Button::Action ) )
   {
      _menu->SelectCurrentOption();
   }
}

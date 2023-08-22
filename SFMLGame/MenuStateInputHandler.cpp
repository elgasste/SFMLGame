#include "MenuStateInputHandler.h"
#include "InputReader.h"
#include "EventQueue.h"
#include "PlayingStateMenu.h"

using namespace NAMESPACE;
using namespace std;

MenuStateInputHandler::MenuStateInputHandler( shared_ptr<InputReader> inputReader,
                                              shared_ptr<EventQueue> eventQueue,
                                              shared_ptr<PlayingStateMenu> menu ) :
   _inputReader( inputReader ),
   _eventQueue( eventQueue ),
   _menu( menu )
{
}

void MenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _eventQueue->Push( GameEventType::CloseMenu );
   }
   else if ( _inputReader->WasButtonPressed( Button::Up ) )
   {
      _menu->ScrollUp();
   }
   else if ( _inputReader->WasButtonPressed( Button::Down ) )
   {
      _menu->ScrollDown();
   }
   else if ( _inputReader->WasButtonPressed( Button::Action ) )
   {
      _menu->SelectCurrentOption();
   }
}

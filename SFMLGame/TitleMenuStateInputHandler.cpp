#include "TitleMenuStateInputHandler.h"
#include "InputReader.h"
#include "EventQueue.h"
#include "TitleMenu.h"

using namespace NAMESPACE;
using namespace std;

TitleMenuStateInputHandler::TitleMenuStateInputHandler( shared_ptr<InputReader> inputReader,
                                                        shared_ptr<EventQueue> eventQueue,
                                                        shared_ptr<TitleMenu> menu ) :
   _inputReader( inputReader ),
   _eventQueue( eventQueue ),
   _menu( menu )
{
}

void TitleMenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Up ) )
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

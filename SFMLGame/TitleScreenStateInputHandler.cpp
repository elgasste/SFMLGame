#include "TitleScreenStateInputHandler.h"
#include "InputReader.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

TitleScreenStateInputHandler::TitleScreenStateInputHandler( shared_ptr<InputReader> inputReader,
                                                            shared_ptr<EventQueue> eventQueue ) :
   _inputReader( inputReader ),
   _eventQueue( eventQueue )
{
}

void TitleScreenStateInputHandler::HandleInput()
{
   if ( _inputReader->WasAnyButtonPressed() )
   {
      _eventQueue->Push( GameEventType::OpenMenu );
   }
}

#include "TitleMenuStateInputHandler.h"
#include "InputReader.h"
#include "EventQueue.h"

using namespace NAMESPACE;
using namespace std;

TitleMenuStateInputHandler::TitleMenuStateInputHandler( shared_ptr<InputReader> inputReader,
                                                        shared_ptr<EventQueue> eventQueue ) :
   _inputReader( inputReader ),
   _eventQueue( eventQueue )
{
}

void TitleMenuStateInputHandler::HandleInput()
{
   if ( _inputReader->WasAnyButtonPressed() )
   {
      _eventQueue->Push( GameEventType::StartGame );
   }
}

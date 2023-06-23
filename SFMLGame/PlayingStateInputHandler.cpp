#include "PlayingStateInputHandler.h"
#include "IInputReader.h"
#include "EventAggregator.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<IInputReader> inputReader,
                                                    shared_ptr<EventAggregator> eventAggregator ) :
   _inputReader( inputReader ),
   _eventAggregator( eventAggregator )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _eventAggregator->RaiseEvent( GameEvent::Quit );
   }
}

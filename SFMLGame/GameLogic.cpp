#include "GameLogic.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "IInputReader.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameConfig> config,
                      shared_ptr<EventAggregator> eventAggregator,
                      shared_ptr<IInputReader> inputReader ) :
   _config( config ),
   _eventAggregator( eventAggregator ),
   _inputReader( inputReader )
{
}

void GameLogic::Tick()
{
   if ( _inputReader->WasButtonPressed( Button::Quit ) )
   {
      _eventAggregator->RaiseEvent( GameEvent::Quit );
   }
   else if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _config->ShowDiagnostics = !_config->ShowDiagnostics;
   }
}

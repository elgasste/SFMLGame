#include "GameInputHandler.h"
#include "GameConfig.h"
#include "IInputReader.h"
#include "EventAggregator.h"
#include "ArenaInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<GameConfig> config,
                                    shared_ptr<IInputReader> inputReader,
                                    shared_ptr<EventAggregator> eventAggregator,
                                    shared_ptr<ArenaInputHandler> arenaInputHandler ) :
   _config( config ),
   _inputReader( inputReader ),
   _eventAggregator( eventAggregator ),
   _arenaInputHandler( arenaInputHandler )
{
}

void GameInputHandler::HandleInput() const
{
   if ( _inputReader->WasButtonPressed( Button::Quit ) )
   {
      _eventAggregator->RaiseEvent( GameEvent::Quit );
      return;
   }

   if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _config->ShowDiagnostics = !_config->ShowDiagnostics;
   }

   _arenaInputHandler->HandleInput();
}

#include "GameInputHandler.h"
#include "GameConfig.h"
#include "IInputReader.h"
#include "EventAggregator.h"
#include "IGameStateInputHandler.h"
#include "GameStateProvider.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<GameConfig> config,
                                    shared_ptr<IInputReader> inputReader,
                                    shared_ptr<EventAggregator> eventAggregator,
                                    map<GameState, shared_ptr<IGameStateInputHandler>> gameStateInputHandlers,
                                    shared_ptr<GameStateProvider> gameStateProvider ) :
   _config( config ),
   _inputReader( inputReader ),
   _eventAggregator( eventAggregator ),
   _gameStateInputHandlers( gameStateInputHandlers ),
   _gameStateProvider( gameStateProvider )
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

   _gameStateInputHandlers.at( _gameStateProvider->GetState() )->HandleInput();
}

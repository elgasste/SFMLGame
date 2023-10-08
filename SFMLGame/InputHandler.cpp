#include "InputHandler.h"
#include "GameConfig.h"
#include "InputStateController.h"
#include "IGameStateInputHandler.h"

using namespace NAMESPACE;
using namespace std;

InputHandler::InputHandler( shared_ptr<GameConfig> gameConfig,
                            shared_ptr<InputStateController> inputReader,
                            shared_ptr<GameStateTracker> gameStateTracker ) :
   _gameConfig( gameConfig ),
   _inputReader( inputReader ),
   _gameStateTracker( gameStateTracker )
{
}

void InputHandler::AddStateInputHandler( GameState state, shared_ptr<IGameStateInputHandler> handler )
{
   _stateInputHandlerMap[state] = handler;
}

void InputHandler::HandleInput()
{
   _stateInputHandlerMap.at( _gameStateTracker->gameState )->HandleInput();

   if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _gameConfig->ShowDiagnostics = !_gameConfig->ShowDiagnostics;
   }
}

#include "GameInputHandler.h"
#include "GameConfig.h"
#include "IInputReader.h"
#include "GameStateController.h"
#include "IGameStateInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<GameConfig> gameConfig,
                                    shared_ptr<IInputReader> inputReader,
                                    shared_ptr<GameStateController> stateController ) :
   _gameConfig( gameConfig ),
   _inputReader( inputReader ),
   _stateController( stateController )
{
}

void GameInputHandler::AddStateInputHandler( GameState state, shared_ptr<IGameStateInputHandler> handler )
{
   _stateInputHandlerMap[state] = handler;
}

void GameInputHandler::HandleInput()
{
   _stateInputHandlerMap.at( _stateController->GetState() )->HandleInput();

   if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _gameConfig->ShowDiagnostics = !_gameConfig->ShowDiagnostics;
   }
}

#include "GameInputHandler.h"
#include "GameConfig.h"
#include "InputReader.h"
#include "IGameStateInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<GameConfig> gameConfig,
                                    shared_ptr<InputReader> inputReader,
                                    shared_ptr<GameStateTracker> gameStateTracker ) :
   _gameConfig( gameConfig ),
   _inputReader( inputReader ),
   _gameStateTracker( gameStateTracker )
{
}

void GameInputHandler::AddStateInputHandler( GameState state, shared_ptr<IGameStateInputHandler> handler )
{
   _stateInputHandlerMap[state] = handler;
}

void GameInputHandler::HandleInput()
{
   _stateInputHandlerMap.at( _gameStateTracker->gameState )->HandleInput();

   if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _gameConfig->ShowDiagnostics = !_gameConfig->ShowDiagnostics;
   }
}

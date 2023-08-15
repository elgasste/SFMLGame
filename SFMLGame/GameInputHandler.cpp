#include "GameInputHandler.h"
#include "GameConfig.h"
#include "GameData.h"
#include "InputReader.h"
#include "IGameStateInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<GameConfig> gameConfig,
                                    shared_ptr<GameData> gameData,
                                    shared_ptr<InputReader> inputReader ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _inputReader( inputReader )
{
}

void GameInputHandler::AddStateInputHandler( GameState state, shared_ptr<IGameStateInputHandler> handler )
{
   _stateInputHandlerMap[state] = handler;
}

void GameInputHandler::HandleInput()
{
   _stateInputHandlerMap.at( _gameData->GetGameState() )->HandleInput();

   if ( _inputReader->WasButtonPressed( Button::Diagnostics ) )
   {
      _gameConfig->ShowDiagnostics = !_gameConfig->ShowDiagnostics;
   }
}

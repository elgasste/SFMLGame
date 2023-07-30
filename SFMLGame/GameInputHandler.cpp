#include "GameInputHandler.h"
#include "RenderConfig.h"
#include "InputReader.h"
#include "GameStateController.h"
#include "IGameStateInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameInputHandler::GameInputHandler( shared_ptr<RenderConfig> renderConfig,
                                    shared_ptr<InputReader> inputReader,
                                    shared_ptr<GameStateController> stateController ) :
   _renderConfig( renderConfig ),
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
      _renderConfig->ShowDiagnostics = !_renderConfig->ShowDiagnostics;
   }
}

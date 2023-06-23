#include "PlayingStateInputHandler.h"
#include "IInputReader.h"
#include "GameStateController.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<IInputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController ) :
   _inputReader( inputReader ),
   _stateController( stateController )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _stateController->SetState( GameState::Menu );
   }
}

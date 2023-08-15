#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameData.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameData> gameData ) :
   _inputReader( inputReader ),
   _gameData( gameData )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _gameData->SetGameState( GameState::Menu );
   }
}

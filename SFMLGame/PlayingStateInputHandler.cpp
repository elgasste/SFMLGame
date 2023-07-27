#include "PlayingStateInputHandler.h"
#include "IInputReader.h"
#include "GameStateController.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<IInputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController,
                                                    shared_ptr<Entity> player ) :
   _inputReader( inputReader ),
   _stateController( stateController ),
   _player( player )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _stateController->SetState( GameState::Menu );
      return;
   }
   
   auto isLeftDown = _inputReader->IsButtonDown( Button::Left );
   auto isRightDown = _inputReader->IsButtonDown( Button::Right );

   // MUFFINS: this should come from a config, or maybe should call some movement controller
   if ( isLeftDown && !isRightDown )
   {
      _player->SetAngle( _player->GetAngle() + 0.02f );
   }
   else if ( isRightDown && !isLeftDown )
   {
      _player->SetAngle( _player->GetAngle() - 0.02f );
   }
}

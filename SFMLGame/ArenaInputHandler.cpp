#include "ArenaInputHandler.h"
#include "GameData.h"
#include "IInputReader.h"
#include "Arena.h"
#include "Player.h"

using namespace NAMESPACE;
using namespace std;

ArenaInputHandler::ArenaInputHandler( shared_ptr<GameData> gameData,
                                      shared_ptr<IInputReader> inputReader,
                                      shared_ptr<Arena> arena ) :
   _gameData( gameData ),
   _inputReader( inputReader ),
   _arena( arena )
{
}

void ArenaInputHandler::HandleInput() const
{
   auto player = _arena->GetPlayer();

   if ( _inputReader->IsButtonDown( Button::Left ) )
   {
      player->SetVelocityX( -_gameData->PlayerMoveVelocity );
      player->SetDirection( Direction::Left );
   }
   else if ( _inputReader->IsButtonDown( Button::Right ) )
   {
      player->SetVelocityX( _gameData->PlayerMoveVelocity );
      player->SetDirection( Direction::Right );
   }
   else
   {
      player->SetVelocityX( 0 );
   }

   if ( _inputReader->IsButtonDown( Button::Up ) )
   {
      player->SetVelocityY( -_gameData->PlayerMoveVelocity );
      player->SetDirection( Direction::Up );
   }
   else if ( _inputReader->IsButtonDown( Button::Down ) )
   {
      player->SetVelocityY( _gameData->PlayerMoveVelocity );
      player->SetDirection( Direction::Down );
   }
   else
   {
      player->SetVelocityY( 0 );
   }
}

#include "Arena.h"
#include "GameData.h"
#include "GameClock.h"
#include "Player.h"
#include "RectUtilities.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Arena::Arena( shared_ptr<GameData> gameData,
              shared_ptr<GameClock> clock,
              shared_ptr<Player> player ) :
   _clock( clock ),
   _player( player )
{
   _bounds = gameData->ArenaBounds;
}

void Arena::Tick()
{
   if ( _player->GetVelocity().x != 0 )
   {
      auto deltaX = _player->GetVelocity().x * _clock->GetFrameSeconds();
      _player->MoveX( deltaX );
   }

   if ( _player->GetVelocity().y != 0 )
   {
      auto deltaY = _player->GetVelocity().y * _clock->GetFrameSeconds();
      _player->MoveY( deltaY );
   }

   auto clampedPosition = _player->GetPosition();
   if ( RectUtilities::ClampRectToBounds( clampedPosition, _player->GetHitBox(), _bounds ) )
   {
      _player->SetPosition( clampedPosition );
   }
}

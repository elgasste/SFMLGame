#include "Arena.h"
#include "GameData.h"
#include "GameClock.h"
#include "Player.h"
#include "Actor.h"
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

void Arena::AddActor( shared_ptr<Actor> actor )
{
   if ( find( _actors.begin(), _actors.end(), actor ) == _actors.end() )
   {
      _actors.push_back( actor );
   }
}

void Arena::RemoveActor( unsigned int uniqueId )
{
   auto it = find_if( _actors.begin(), _actors.end(), [&uniqueId]( shared_ptr<Actor> actor )
   {
      return actor->GetUniqueId() == uniqueId;
   } );

   if ( it != _actors.end() )
   {
      _actors.erase( it );
   }
}

void Arena::Tick()
{
   MoveEntity( _player );

   for ( auto actor : _actors )
   {
      actor->Tick();
      MoveEntity( actor );
   }
}

void Arena::MoveEntity( shared_ptr<Entity> entity ) const
{
   if ( entity->GetVelocity().x != 0 )
   {
      auto deltaX = entity->GetVelocity().x * _clock->GetFrameSeconds();
      entity->MoveX( deltaX );
   }

   if ( _player->GetVelocity().y != 0 )
   {
      auto deltaY = entity->GetVelocity().y * _clock->GetFrameSeconds();
      entity->MoveY( deltaY );
   }

   auto clampedPosition = entity->GetPosition();
   if ( RectUtilities::ClampRectToBounds( clampedPosition, entity->GetHitBox(), _bounds ) )
   {
      entity->SetPosition( clampedPosition );
   }
}

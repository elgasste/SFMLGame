#include "GameLogic.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameStateProvider.h"
#include "EventAggregator.h"
#include "CommandAggregator.h"
#include "MovePlayerCommandArgs.h"
#include "GameInputHandler.h"
#include "Arena.h"
#include "Player.h"
#include "Actor.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameConfig> config,
                      shared_ptr<GameData> gameData,
                      shared_ptr<GameStateProvider> gameStateProvider,
                      shared_ptr<EventAggregator> eventAggregator,
                      shared_ptr<CommandAggregator> commandAggregator,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<Arena> arena ) :
   _config( config ),
   _gameData( gameData ),
   _gameStateProvider( gameStateProvider ),
   _eventAggregator( eventAggregator ),
   _inputHandler( inputHandler ),
   _arena( arena )
{
   commandAggregator->RegisterExecutor( this );
}

void GameLogic::Start()
{
   // MUFFINS: spawn the NPC in a random location?
   _arena->AddActor( _gameData->Npc );

   _gameStateProvider->SetState( GameState::Playing );
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   if ( _gameStateProvider->GetState() == GameState::Playing )
   {
      _arena->Tick();
   }
}

void GameLogic::ExecuteCommand( GameCommand command, void* args )
{
   if ( _gameStateProvider->GetState() == GameState::Loading )
   {
      return;
   }

   auto player = _arena->GetPlayer();

   if ( command == GameCommand::MovePlayer )
   {
      auto moveArgs = (MovePlayerCommandArgs*)args;
      player->SetDirection( moveArgs->direction );

      switch ( moveArgs->direction )
      {
         case Direction::Left:
            player->SetVelocityX( -moveArgs->velocity );
            break;
         case Direction::Up:
            player->SetVelocityY( -moveArgs->velocity );
            break;
         case Direction::Right:
            player->SetVelocityX( moveArgs->velocity );
            break;
         case Direction::Down:
            player->SetVelocityY( moveArgs->velocity );
            break;
      }
   }
   else if ( command == GameCommand::StopPlayerX )
   {
      player->SetVelocityX( 0 );
   }
   else if ( command == GameCommand::StopPlayerY )
   {
      player->SetVelocityY( 0 );
   }
}

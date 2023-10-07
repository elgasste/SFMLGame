#include "GameConfig.h"
#include "GameLogic.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "Collider.h"
#include "Entity.h"
#include "Geometry.h"
#include "TurnPlayerArgs.h"
#include "MovePlayerArgs.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameConfig> gameConfig,
                      shared_ptr<GameData> gameData,
                      shared_ptr<RenderConfig> renderConfig,
                      shared_ptr<EventQueue> eventQueue,
                      shared_ptr<GameClock> clock,
                      shared_ptr<Collider> collider,
                      shared_ptr<GameRunningTracker> gameRunningTracker,
                      shared_ptr<GameStateTracker> gameStateTracker ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _eventQueue( eventQueue ),
   _clock( clock ),
   _collider( collider ),
   _gameRunningTracker( gameRunningTracker ),
   _gameStateTracker( gameStateTracker )
{
   gameStateTracker->gameState = GameState::TitleMenu;
}

void GameLogic::Tick()
{
   _gameData->GetPlayer()->SetIsMoving( false );

   HandleEvents();
}

void GameLogic::ResetPlayer()
{
   auto player = _gameData->GetPlayer();

   player->SetPosition( _gameConfig->DefaultPlayerPosition.x, _gameConfig->DefaultPlayerPosition.y );
   player->SetDirection( _gameConfig->DefaultPlayerDirection );
}

void GameLogic::HandleEvents()
{
   while ( _eventQueue->HasEvents() )
   {
      auto event = _eventQueue->GetNext();

      switch ( event.type )
      {
         case GameEventType::Quit:        OnQuit();                    break;
         case GameEventType::ExitToTitle: OnExitToTitle();             break;
         case GameEventType::OpenMenu:    OnOpenMenu();                break;
         case GameEventType::CloseMenu:   OnCloseMenu();               break;
         case GameEventType::StartGame:   OnStartGame();               break;
         case GameEventType::TurnPlayer:  OnTurnPlayer( event.args );  break;
         case GameEventType::MovePlayer:  OnMovePlayer( event.args );  break;
      }
   }
}

void GameLogic::OnQuit() const
{
   // TODO: whatever needs to be done to clean up (saving the game, etc)
   _gameRunningTracker->isRunning = false;
   _gameStateTracker->gameState = GameState::Closing;
   _eventQueue->Flush();
}

void GameLogic::OnExitToTitle() const
{
   _gameStateTracker->gameState = GameState::TitleMenu;
   _eventQueue->Flush();
}

void GameLogic::OnOpenMenu() const
{
   if ( _gameStateTracker->gameState == GameState::Playing )
   {
      _gameStateTracker->gameState = GameState::MainMenu;
      _eventQueue->Flush();
   }
}

void GameLogic::OnCloseMenu() const
{
   switch ( _gameStateTracker->gameState )
   {
      case GameState::MainMenu:
         _gameStateTracker->gameState = GameState::Playing;
         _eventQueue->Flush();
         break;
      case GameState::TitleMenu:
         OnQuit();
         break;
   }
}

void GameLogic::OnStartGame()
{
   ResetPlayer();
   _gameStateTracker->gameState = GameState::Playing;
   _eventQueue->Flush();
}

void GameLogic::OnTurnPlayer( shared_ptr<IGameEventArgs> args ) const
{
   auto turnArgs = (TurnPlayerArgs*)( args.get() );
   _gameData->GetPlayer()->SetDirection( turnArgs->GetDirection() );
}

void GameLogic::OnMovePlayer( shared_ptr<IGameEventArgs> args ) const
{
   auto moveArgs = (MovePlayerArgs*)( args.get() );
   _collider->MoveEntity( _gameData->GetPlayer(),
                          moveArgs->GetDirection(),
                          moveArgs->GetVelocity() * _clock->GetFrameSeconds() );
}

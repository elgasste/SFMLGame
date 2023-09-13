#include "GameConfig.h"
#include "GameLogic.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "GameInputHandler.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "GameRunningTracker.h"
#include "Entity.h"
#include "Geometry.h"
#include "TurnPlayerArgs.h"
#include "MovePlayerArgs.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameConfig> gameConfig,
                      shared_ptr<GameData> gameData,
                      shared_ptr<RenderConfig> renderConfig,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<EventQueue> eventQueue,
                      shared_ptr<GameClock> clock,
                      shared_ptr<GameRunningTracker> gameRunningTracker,
                      shared_ptr<GameStateTracker> gameStateTracker ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _inputHandler( inputHandler ),
   _eventQueue( eventQueue ),
   _clock( clock ),
   _gameRunningTracker( gameRunningTracker ),
   _gameStateTracker( gameStateTracker )
{
   gameStateTracker->gameState = GameState::TitleMenu;
}

void GameLogic::Tick()
{
   _gameData->GetPlayer()->SetIsMoving( false );

   _inputHandler->HandleInput();
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
   auto player = _gameData->GetPlayer();
   auto moveArgs = (MovePlayerArgs*)( args.get() );

   auto direction = moveArgs->GetDirection();
   auto& currentPosition = player->GetPosition();
   player->SetIsMoving( true );

   switch ( direction )
   {
      case Direction::Left:
         player->SetPosition( currentPosition.x - ( _gameConfig->PlayerVelocityIncrement * _clock->GetFrameSeconds() ), currentPosition.y );
         break;
      case Direction::Up:
         player->SetPosition( currentPosition.x, currentPosition.y - ( _gameConfig->PlayerVelocityIncrement * _clock->GetFrameSeconds() ) );
         break;
      case Direction::Right:
         player->SetPosition( currentPosition.x + ( _gameConfig->PlayerVelocityIncrement * _clock->GetFrameSeconds() ), currentPosition.y );
         break;
      case Direction::Down:
         player->SetPosition( currentPosition.x, currentPosition.y + ( _gameConfig->PlayerVelocityIncrement * _clock->GetFrameSeconds() ) );
         break;
   }

   ClipPlayer();
}

void GameLogic::ClipPlayer() const
{
   auto player = _gameData->GetPlayer();
   auto& position = player->GetPosition();
   auto& hitBoxOffset = player->GetHitBoxOffset();

   if ( ( position.y + hitBoxOffset.y ) < 0 )
   {
      // hit the top edge of the arena
      player->SetPosition( position.x, -hitBoxOffset.y );
   }
   else if ( ( position.y - hitBoxOffset.y ) >= ( _renderConfig->ViewHeight - 1 ) )
   {
      // hit the bottom edge of the arena
      player->SetPosition( position.x, ( _renderConfig->ViewHeight - 1 ) + hitBoxOffset.y );
   }

   if ( ( position.x + hitBoxOffset.x ) < 0 )
   {
      // hit the left edge of the arena
      player->SetPosition( -hitBoxOffset.x, position.y );
   }
   else if ( ( position.x - hitBoxOffset.x ) >= ( _renderConfig->ViewWidth - 1 ) )
   {
      // hit the right edge of the arena
      player->SetPosition( ( _renderConfig->ViewWidth - 1 ) + hitBoxOffset.x, position.y );
   }
}

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
#include "TurnBallArgs.h"
#include "PushBallArgs.h"

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
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();
   HandleEvents();

   if ( _gameStateTracker->gameState == GameState::Playing )
   {
      UpdateBallPosition();
      ClipBall();
   }
}

void GameLogic::HandleEvents()
{
   while ( _eventQueue->HasEvents() )
   {
      auto event = _eventQueue->GetNext();

      switch ( event.type )
      {
         case GameEventType::Quit:        OnQuit();                  break;
         case GameEventType::OpenMenu:    OnOpenMenu();              break;
         case GameEventType::CloseMenu:   OnCloseMenu();             break;
         case GameEventType::TurnBall:    OnTurnBall( event.args );  break;
         case GameEventType::PushBall:    OnPushBall( event.args );  break;
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

void GameLogic::OnOpenMenu() const
{
   if ( _gameStateTracker->gameState == GameState::Playing )
   {
      _gameStateTracker->gameState = GameState::Menu;
      _eventQueue->Flush();
   }
}

void GameLogic::OnCloseMenu() const
{
   if ( _gameStateTracker->gameState == GameState::Menu )
   {
      _gameStateTracker->gameState = GameState::Playing;
      _eventQueue->Flush();
   }
}

void GameLogic::OnTurnBall( shared_ptr<IGameEventArgs> args ) const
{
   auto ball = _gameData->GetBall();
   auto turnArgs = (TurnBallArgs*)( args.get() );

   auto newAngle = ball->GetAngle() + ( turnArgs->GetIncrement() * _clock->GetFrameSeconds() );
   NORMALIZE_ANGLE( newAngle );

   ball->SetAngle( newAngle );
}

void GameLogic::OnPushBall( shared_ptr<IGameEventArgs> args ) const
{
   auto ball = _gameData->GetBall();
   auto pushArgs = (PushBallArgs*)( args.get() );

   auto newVelocity = ball->GetVelocity() + ( pushArgs->GetIncrement() * _clock->GetFrameSeconds() );
   ball->SetVelocity( min( newVelocity, _gameConfig->MaximumBallVelocity ) );
}

void GameLogic::UpdateBallPosition() const
{
   auto ball = _gameData->GetBall();
   auto& position = ball->GetPosition();
   auto angle = ball->GetAngle();
   auto velocity = ball->GetVelocity();

   auto dx = cosf( angle ) * ( velocity * _clock->GetFrameSeconds() );
   auto dy = tanf( angle ) * dx;

   auto newPositionX = position.x + dx;
   auto newPositionY = position.y - dy;

   ball->SetPosition( newPositionX, newPositionY );
}

void GameLogic::ClipBall() const
{
   auto ball = _gameData->GetBall();
   auto& hitBox = ball->GetHitBox();

   if ( hitBox.top < 0 )
   {
      // hit the top edge of the arena
      ball->SetPosition( ball->GetPosition().x, ( hitBox.height / 2.0f ) );
      auto newAngle = RAD_360 - ball->GetAngle();
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }
   else if ( ( hitBox.top + hitBox.height ) >= ( _renderConfig->ScreenHeight - 1 ) )
   {
      // hit the bottom edge of the arena
      ball->SetPosition( ball->GetPosition().x, ( _renderConfig->ScreenHeight - 1 ) - ( hitBox.height / 2.0f ) );
      auto newAngle = RAD_360 - ball->GetAngle();
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }

   if ( hitBox.left < 0 )
   {
      // hit the left edge of the arena
      ball->SetPosition( ( hitBox.width / 2.0f ), ball->GetPosition().y );
      auto newAngle = RAD_180 - ball->GetAngle();
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }
   else if ( ( hitBox.left + hitBox.width ) >= ( _renderConfig->ScreenWidth - 1 ) )
   {
      // hit the right edge of the arena
      ball->SetPosition( ( _renderConfig->ScreenWidth - 1 ) - ( hitBox.width / 2.0f ), ball->GetPosition().y );
      auto newAngle = RAD_180 - ball->GetAngle();
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }
}

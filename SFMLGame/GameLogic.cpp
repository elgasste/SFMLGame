#include "GameLogic.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "GameInputHandler.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameData> gameData,
                      shared_ptr<RenderConfig> renderConfig,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<EventAggregator> eventAggregator,
                      shared_ptr<GameClock> clock ) :
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _inputHandler( inputHandler ),
   _eventAggregator( eventAggregator ),
   _clock( clock )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();
   HandleEvents();

   if ( _gameData->GetGameState() == GameState::Playing )
   {
      UpdateBallPosition();
      ClipBall();
   }
}

void GameLogic::HandleEvents() const
{
   while ( _eventAggregator->HasEvents() )
   {
      auto event = _eventAggregator->GetNextEvent();

      if ( event == GameEvent::Quit )
      {
         // TODO: quit the game
      }
   }
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

#include "GameLogic.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "GameInputHandler.h"
#include "GameClock.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameData> gameData,
                      shared_ptr<RenderConfig> renderConfig,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<GameClock> clock ) :
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _inputHandler( inputHandler ),
   _clock( clock )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   UpdateBallPosition();
   ClipBall();
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
      // we've hit the top of the arena
      ball->SetPosition( ball->GetPosition().x, ( hitBox.height / 2.0f ) );
   }
   else if ( ( hitBox.top + hitBox.height ) >= ( _renderConfig->ScreenHeight - 1 ) )
   {
      // we've hit the bottom of the arena
      ball->SetPosition( ball->GetPosition().x, ( _renderConfig->ScreenHeight - 1 ) - ( hitBox.height / 2.0f ) );
   }

   if ( hitBox.left < 0 )
   {
      // we've hit the left of the arena
      ball->SetPosition( ( hitBox.width / 2.0f ), ball->GetPosition().y );
   }
   else if ( ( hitBox.left + hitBox.width ) >= ( _renderConfig->ScreenWidth - 1 ) )
   {
      // we've hit the right of the arena
      ball->SetPosition( ( _renderConfig->ScreenWidth - 1 ) - ( hitBox.width / 2.0f ), ball->GetPosition().y );
   }
}

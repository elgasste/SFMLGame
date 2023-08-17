#include "GameLogic.h"
#include "GameData.h"
#include "GameInputHandler.h"
#include "GameClock.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameData> gameData,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<GameClock> clock ) :
   _gameData( gameData ),
   _inputHandler( inputHandler ),
   _clock( clock )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

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

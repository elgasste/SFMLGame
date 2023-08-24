#include <math.h>

#include "GameLogic.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameClock.h"
#include "GameInputHandler.h"
#include "BspOperator.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameLogic::GameLogic( shared_ptr<GameConfig> gameConfig,
                      shared_ptr<GameData> gameData,
                      shared_ptr<GameClock> clock,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<BspOperator> bspOperator ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _clock( clock ),
   _inputHandler( inputHandler ),
   _bspOperator( bspOperator )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();
   MovePlayer();
}

void GameLogic::MovePlayer() const
{
   auto player = _gameData->GetPlayer();

   auto forwardVelocity = player->GetForwardVelocity();
   auto sidewaysVelocity = player->GetSidewaysVelocity();

   if ( forwardVelocity == 0 && sidewaysVelocity == 0 )
   {
      return;
   }

   auto& position = player->GetPosition();
   auto forwardAngle = player->GetAngle();
   auto sidewaysAngle = forwardAngle + RAD_90;
   NORMALIZE_ANGLE( sidewaysAngle );

   // forward/backward movement
   auto dx = cosf( forwardAngle ) * ( forwardVelocity * _clock->GetFrameSeconds() );
   auto dy = tanf( forwardAngle ) * dx;
   auto newPositionX = position.x + dx;
   auto newPositionY = position.y - dy;

   // sideways movement
   dx = cosf( sidewaysAngle ) * ( sidewaysVelocity * _clock->GetFrameSeconds() );
   dy = tanf( sidewaysAngle ) * dx;
   newPositionX -= dx;
   newPositionY += dy;

   // check for wall collision
   //
   // MUFFINS: try to "hug" the wall if this happens
   auto collidedWithWall = _bspOperator->CheckWallCollision( position.x, position.y, newPositionX, newPositionY );

   if ( !collidedWithWall )
   {
      player->SetPosition( newPositionX, newPositionY );
   }

   // finally, decelerate
   DeceleratePlayer( player, collidedWithWall );
}

void GameLogic::DeceleratePlayer( shared_ptr<Entity> player, bool collidedWithWall ) const
{
   if ( collidedWithWall )
   {
      // MUFFINS: this will probably change (maybe even go away entirely?) when
      // we figure out how to "hug" walls and move along them
      player->SetForwardVelocity( 0 );
      player->SetSidewaysVelocity( 0 );
      return;
   }

   auto forwardVelocity = player->GetForwardVelocity();
   auto sidewaysVelocity = player->GetSidewaysVelocity();

   auto newForwardVelocity = ( forwardVelocity > 0 )
      ? max( 0.0f, forwardVelocity - ( _gameConfig->PlayerVelocityDeceleration * _clock->GetFrameSeconds() ) )
      : min( 0.0f, forwardVelocity + ( _gameConfig->PlayerVelocityDeceleration * _clock->GetFrameSeconds() ) );
   auto newSidewaysVelocity = ( sidewaysVelocity > 0 )
      ? max( 0.0f, sidewaysVelocity - ( _gameConfig->PlayerVelocityDeceleration * _clock->GetFrameSeconds() ) )
      : min( 0.0f, sidewaysVelocity + ( _gameConfig->PlayerVelocityDeceleration * _clock->GetFrameSeconds() ) );

   player->SetForwardVelocity( newForwardVelocity );
   player->SetSidewaysVelocity( newSidewaysVelocity );
}

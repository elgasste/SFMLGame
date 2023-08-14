#include <math.h>

#include "GameLogic.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameInputHandler.h"
#include "BspOperator.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameLogic::GameLogic( shared_ptr<GameConfig> gameConfig,
                      shared_ptr<GameData> gameData,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<BspOperator> bspOperator ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
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

   auto position = player->GetPosition();
   auto forwardAngle = player->GetAngle();
   auto sidewaysAngle = forwardAngle + RAD_90;
   NORMALIZE_ANGLE( sidewaysAngle );

   // forward/backward movement
   auto dx = cosf( forwardAngle ) * forwardVelocity;
   auto dy = tanf( forwardAngle ) * dx;
   auto newPositionX = position.x + dx;
   auto newPositionY = position.y - dy;

   // sideways movement
   dx = cosf( sidewaysAngle ) * sidewaysVelocity;
   dy = tanf( sidewaysAngle ) * dx;
   newPositionX -= dx;
   newPositionY += dy;

   // check for wall collision
   auto collidedWithWall = EntityCollidedWithWall( player, newPositionX, newPositionY );

   if ( !collidedWithWall )
   {
      player->SetPosition( newPositionX, newPositionY );
   }

   // finally, decelerate
   DeceleratePlayer( player, collidedWithWall );
}

bool GameLogic::EntityCollidedWithWall( std::shared_ptr<Entity> entity, float xDest, float yDest ) const
{
   auto position = entity->GetPosition();
   auto subsector = _bspOperator->GetOccupyingSubsector( entity );

   // MUFFINS: take the entity's hit box into consideration. but HOW?? I think using a radius would be
   // pretty neat, and would solve some issues of how to clip to a wall, but it's tough when the
   // hit box might span several subsectors. I think there's a way to use the BSP tree to do it, but
   // I'm not really sure how? guess I'll have to do some research. Doom uses "blockmaps", I'm not
   // even sure how those work.
   for ( const auto& lineseg : subsector.linesegs )
   {
      // MUFFINS: if there's a collision, we should try "hugging" the wall and moving along it
      if ( Geometry::LinesIntersect( position.x, position.y, xDest, yDest,
                                     lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y,
                                     nullptr ) )
      {
         return true;
         break;
      }
   }

   return false;
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
      ? max( 0.0f, forwardVelocity - _gameConfig->PlayerVelocityDeceleration )
      : min( 0.0f, forwardVelocity + _gameConfig->PlayerVelocityDeceleration );
   auto newSidewaysVelocity = ( sidewaysVelocity > 0 )
      ? max( 0.0f, sidewaysVelocity - _gameConfig->PlayerVelocityDeceleration )
      : min( 0.0f, sidewaysVelocity + _gameConfig->PlayerVelocityDeceleration );

   player->SetForwardVelocity( newForwardVelocity );
   player->SetSidewaysVelocity( newSidewaysVelocity );
}

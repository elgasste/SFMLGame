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

void GameLogic::MovePlayer()
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

   // MUFFINS: factor in the player's radius somewhere in here

   // check for wall collisions
   auto subsector = _bspOperator->GetOccupyingSubsector( player );
   bool collisionDetected = false;

   for ( const auto& lineseg : subsector.linesegs )
   {
      // MUFFINS: if there's a collision, we should try "hugging" the wall, I think?
      // this will be more fleshed-out when hit boxes are implemented, probably.
      if ( Geometry::LinesIntersect( position.x, position.y, newPositionX, newPositionY,
                                     lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y,
                                     nullptr ) )
      {
         collisionDetected = true;
         break;
      }
   }

   if ( !collisionDetected )
   {
      player->SetPosition( Vector2f( newPositionX, newPositionY ) );
   }

   // decelerate
   auto newForwardVelocity = ( forwardVelocity > 0 )
      ? max( 0.0f, forwardVelocity - _gameConfig->PlayerVelocityDeceleration )
      : min( 0.0f, forwardVelocity + _gameConfig->PlayerVelocityDeceleration );
   auto newSidewaysVelocity = ( sidewaysVelocity > 0 )
      ? max( 0.0f, sidewaysVelocity - _gameConfig->PlayerVelocityDeceleration )
      : min( 0.0f, sidewaysVelocity + _gameConfig->PlayerVelocityDeceleration );

   player->SetForwardVelocity( newForwardVelocity );
   player->SetSidewaysVelocity( newSidewaysVelocity );
}

// MUFFINS: can remove a lot of these when movement goes into a different class
#include <math.h>
#include <SFML/System/Vector2.hpp>

#include "PlayingStateInputHandler.h"
#include "IInputReader.h"
#include "GameStateController.h"
#include "Entity.h"
#include "BspRunner.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<IInputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController,
                                                    shared_ptr<Entity> player,
                                                    shared_ptr<BspRunner> bspRunner ) :
   _inputReader( inputReader ),
   _stateController( stateController ),
   _player( player ),
   _bspRunner( bspRunner )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _stateController->SetState( GameState::Menu );
      return;
   }

   // MUFFINS: all of this should be handled in some kind of movement controller

   auto playerAngle = _player->GetAngle();
   auto playerPosition = _player->GetPosition();

   auto isTurningLeft = _inputReader->IsButtonDown( Button::Left );
   auto isTurningRight = _inputReader->IsButtonDown( Button::Right );

   if ( isTurningLeft && !isTurningRight )
   {
      _player->SetAngle( playerAngle + 0.02f );
   }
   else if ( isTurningRight && !isTurningLeft )
   {
      _player->SetAngle( playerAngle - 0.02f );
   }

   auto isMovingForward = _inputReader->IsButtonDown( Button::Forward );
   auto isMovingBackward = _inputReader->IsButtonDown( Button::Backward );
   auto isStrafingLeft = _inputReader->IsButtonDown( Button::StrafeLeft );
   auto isStrafingRight = _inputReader->IsButtonDown( Button::StrafeRight );

   if ( !isMovingForward && !isMovingBackward && !isStrafingLeft && !isStrafingRight )
   {
      return;
   }

   auto dxMove = 0.0f;
   auto dyMove = 0.0f;
   auto dxStrafe = 0.0f;
   auto dyStrafe = 0.0f;

   if ( isMovingForward && !isMovingBackward )
   {
      dxMove = cosf( playerAngle ) * 1.2f;
      dyMove = -( tanf( playerAngle ) * dxMove );
      //_player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }
   else if ( isMovingBackward && !isMovingForward )
   {
      dxMove = -( cosf( playerAngle ) * 1.2f );
      dyMove = tanf( playerAngle ) * dxMove;
      //_player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }

   if ( isStrafingLeft && !isStrafingRight )
   {
      auto strafeAngle = playerAngle + RAD_90;
      NORMALIZE_ANGLE( strafeAngle );
      dxStrafe = cosf( strafeAngle ) * 1.2f;
      dyStrafe = -( tanf( strafeAngle ) * dxStrafe );
      //_player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }
   else if ( isStrafingRight && !isStrafingLeft )
   {
      auto strafeAngle = playerAngle - RAD_90;
      NORMALIZE_ANGLE( strafeAngle );
      dxStrafe = cosf( strafeAngle ) * 1.2f;
      dyStrafe = -( tanf( strafeAngle ) * dxStrafe );
      //_player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }

   auto newPlayerPositionX = playerPosition.x + dxMove + dxStrafe;
   auto newPlayerPositionY = playerPosition.y + dyMove + dyStrafe;

   // check for wall collisions
   //
   // MUFFINS: this isn't really working, and I don't know why...
   auto subsector = _bspRunner->GetOccupyingSubsector( _player );

   for ( const auto& lineseg : subsector.linesegs )
   {
      if ( Geometry::LinesIntersect( playerPosition.x, playerPosition.y, newPlayerPositionX, newPlayerPositionY,
                                     lineseg.start.x, lineseg.start.y, lineseg.end.x, lineseg.end.y, nullptr ) )
      {
         return;
      }
   }

   _player->SetPosition( Vector2f( newPlayerPositionX, newPlayerPositionY ) );
}

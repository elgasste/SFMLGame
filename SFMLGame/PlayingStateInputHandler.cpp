// MUFFINS: can remove a lot of these when movement goes into a different class
#include <math.h>
#include <SFML/System/Vector2.hpp>

#include "PlayingStateInputHandler.h"
#include "IInputReader.h"
#include "GameStateController.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<IInputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController,
                                                    shared_ptr<Entity> player ) :
   _inputReader( inputReader ),
   _stateController( stateController ),
   _player( player )
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

   if ( isMovingForward && !isMovingBackward )
   {
      auto dx = cosf( playerAngle ) * 1.2f;
      auto dy = tanf( playerAngle ) * dx;
      _player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y - dy ) );
   }
   else if ( isMovingBackward && !isMovingForward )
   {
      auto dx = cosf( playerAngle ) * 1.2f;
      auto dy = tanf( playerAngle ) * dx;
      _player->SetPosition( Vector2f( playerPosition.x - dx, playerPosition.y + dy ) );
   }

   auto isStrafingLeft = _inputReader->IsButtonDown( Button::StrafeLeft );
   auto isStrafingRight = _inputReader->IsButtonDown( Button::StrafeRight );

   if ( isStrafingLeft && !isStrafingRight )
   {
      auto strafeAngle = playerAngle + RAD_90;
      NORMALIZE_ANGLE( strafeAngle );
      auto dx = cosf( strafeAngle ) * 1.2f;
      auto dy = -( tanf( strafeAngle ) * dx );
      _player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }
   else if ( isStrafingRight && !isStrafingLeft )
   {
      auto strafeAngle = playerAngle - RAD_90;
      NORMALIZE_ANGLE( strafeAngle );
      auto dx = cosf( strafeAngle ) * 1.2f;
      auto dy = -( tanf( strafeAngle ) * dx );
      _player->SetPosition( Vector2f( playerPosition.x + dx, playerPosition.y + dy ) );
   }
}

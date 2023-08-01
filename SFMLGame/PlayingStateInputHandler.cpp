#include <math.h>

#include "PlayingStateInputHandler.h"
#include "GameConfig.h"
#include "InputReader.h"
#include "GameStateController.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController,
                                                    shared_ptr<Entity> player ) :
   _gameConfig( gameConfig ),
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

   HandlePlayerTurning();
   HandlePlayerMovement();
}

void PlayingStateInputHandler::HandlePlayerTurning() const
{
   auto angle = _player->GetAngle();
   auto isTurningLeft = _inputReader->IsButtonDown( Button::Left );
   auto isTurningRight = _inputReader->IsButtonDown( Button::Right );

   if ( isTurningLeft && !isTurningRight )
   {
      _player->SetAngle( angle += _gameConfig->KeyboardTurnAngleIncrement );
   }
   else if ( isTurningRight && !isTurningLeft )
   {
      _player->SetAngle( angle -= _gameConfig->KeyboardTurnAngleIncrement );
   }

   auto mouseDeltaX = _inputReader->GetMouseDelta().x;

   if ( mouseDeltaX != 0 )
   {
      _player->SetAngle( angle - ( mouseDeltaX * _gameConfig->MouseMoveAngleIncrement ) );
   }
}

void PlayingStateInputHandler::HandlePlayerMovement() const
{
   auto isMovingForward = _inputReader->IsButtonDown( Button::Forward );
   auto isMovingBackward = _inputReader->IsButtonDown( Button::Backward );
   auto isStrafingLeft = _inputReader->IsButtonDown( Button::StrafeLeft );
   auto isStrafingRight = _inputReader->IsButtonDown( Button::StrafeRight );

   if ( !isMovingForward && !isMovingBackward && !isStrafingLeft && !isStrafingRight )
   {
      return;
   }

   auto forwardVelocity = _player->GetForwardVelocity();

   if ( isMovingForward && !isMovingBackward )
   {
      _player->SetForwardVelocity( min( forwardVelocity + _gameConfig->PlayerVelocityAcceleration, _gameConfig->MaxPlayerVelocity ) );
   }
   else if ( isMovingBackward && !isMovingForward )
   {
      _player->SetForwardVelocity( max( forwardVelocity - _gameConfig->PlayerVelocityAcceleration, -( _gameConfig->MaxPlayerVelocity ) ) );
   }

   auto sidewaysVelocity = _player->GetSidewaysVelocity();

   if ( isStrafingLeft && !isStrafingRight )
   {
      _player->SetSidewaysVelocity( max( sidewaysVelocity - _gameConfig->PlayerVelocityAcceleration, -( _gameConfig->MaxPlayerVelocity ) ) );
   }
   else if ( isStrafingRight && !isStrafingLeft )
   {
      _player->SetSidewaysVelocity( min( sidewaysVelocity + _gameConfig->PlayerVelocityAcceleration, _gameConfig->MaxPlayerVelocity ) );
   }
}

#include <math.h>

#include "PlayingStateInputHandler.h"
#include "GameConfig.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameStateController.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<GameData> gameData,
                                                    shared_ptr<RenderConfig> renderConfig,
                                                    shared_ptr<GameClock> clock,
                                                    shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameStateController> stateController ) :
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _renderConfig( renderConfig ),
   _clock( clock ),
   _inputReader( inputReader ),
   _stateController( stateController )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _stateController->SetState( GameState::Menu );
      return;
   }
   else if ( _inputReader->WasButtonPressed( Button::AutoMapToggle ) )
   {
      _renderConfig->ShowTopDownView = !_renderConfig->ShowTopDownView;
      return;
   }

   HandlePlayerTurning();
   HandlePlayerMovement();
}

void PlayingStateInputHandler::HandlePlayerTurning() const
{
   auto player = _gameData->GetPlayer();
   auto angle = player->GetAngle();
   auto isTurningLeft = _inputReader->IsButtonDown( Button::Left );
   auto isTurningRight = _inputReader->IsButtonDown( Button::Right );

   if ( isTurningLeft && !isTurningRight )
   {
      player->SetAngle( angle += _gameConfig->KeyboardTurnAngleIncrement );
   }
   else if ( isTurningRight && !isTurningLeft )
   {
      player->SetAngle( angle -= _gameConfig->KeyboardTurnAngleIncrement );
   }

   auto mouseDeltaX = _inputReader->GetMouseDelta().x;

   if ( mouseDeltaX != 0 )
   {
      player->SetAngle( angle - ( mouseDeltaX * _gameConfig->MouseMoveAngleIncrement ) );
   }
}

void PlayingStateInputHandler::HandlePlayerMovement() const
{
   auto player = _gameData->GetPlayer();
   auto isMovingForward = _inputReader->IsButtonDown( Button::Forward );
   auto isMovingBackward = _inputReader->IsButtonDown( Button::Backward );
   auto isStrafingLeft = _inputReader->IsButtonDown( Button::StrafeLeft );
   auto isStrafingRight = _inputReader->IsButtonDown( Button::StrafeRight );

   if ( !isMovingForward && !isMovingBackward && !isStrafingLeft && !isStrafingRight )
   {
      return;
   }

   auto forwardVelocity = player->GetForwardVelocity();

   if ( isMovingForward && !isMovingBackward )
   {
      player->SetForwardVelocity( min( forwardVelocity + ( _gameConfig->PlayerVelocityAcceleration * _clock->GetFrameSeconds() ), _gameConfig->MaxPlayerVelocity ) );
   }
   else if ( isMovingBackward && !isMovingForward )
   {
      player->SetForwardVelocity( max( forwardVelocity - ( _gameConfig->PlayerVelocityAcceleration * _clock->GetFrameSeconds() ), -( _gameConfig->MaxPlayerVelocity ) ));
   }

   auto sidewaysVelocity = player->GetSidewaysVelocity();

   if ( isStrafingLeft && !isStrafingRight )
   {
      player->SetSidewaysVelocity( max( sidewaysVelocity - ( _gameConfig->PlayerVelocityAcceleration * _clock->GetFrameSeconds() ), -( _gameConfig->MaxPlayerVelocity ) ));
   }
   else if ( isStrafingRight && !isStrafingLeft )
   {
      player->SetSidewaysVelocity( min( sidewaysVelocity + ( _gameConfig->PlayerVelocityAcceleration * _clock->GetFrameSeconds() ), _gameConfig->MaxPlayerVelocity ));
   }
}

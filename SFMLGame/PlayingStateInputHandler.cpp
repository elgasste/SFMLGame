#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameClock.h"
#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<GameData> gameData,
                                                    shared_ptr<GameClock> clock ) :
   _inputReader( inputReader ),
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _clock( clock )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _gameData->SetGameState( GameState::Menu );
      return;
   }

   auto ball = _gameData->GetBall();
   bool isLeftDown = _inputReader->IsButtonDown( Button::Left );
   bool isRightDown = _inputReader->IsButtonDown( Button::Right );

   if ( isLeftDown && !isRightDown )
   {
      auto newAngle = ball->GetAngle() + ( _gameConfig->BallTurnAngleIncrement * _clock->GetFrameSeconds() );
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }
   else if ( isRightDown && !isLeftDown )
   {
      auto newAngle = ball->GetAngle() - ( _gameConfig->BallTurnAngleIncrement * _clock->GetFrameSeconds() );
      NORMALIZE_ANGLE( newAngle );
      ball->SetAngle( newAngle );
   }

   bool isForwardDown = _inputReader->IsButtonDown( Button::Up );
   bool isBackwardDown = _inputReader->IsButtonDown( Button::Down );

   if ( isForwardDown && !isBackwardDown )
   {
      auto newVelocity = ball->GetVelocity() + ( _gameConfig->BallVelocityIncrement * _clock->GetFrameSeconds() );
      ball->SetVelocity( min( newVelocity, _gameConfig->MaximumBallVelocity ) );
   }
   else if ( isBackwardDown && !isForwardDown )
   {
      auto newVelocity = ball->GetVelocity() - ( _gameConfig->BallVelocityIncrement * _clock->GetFrameSeconds() );
      ball->SetVelocity( max( newVelocity, _gameConfig->MinimumBallVelocity ) );
   }
}

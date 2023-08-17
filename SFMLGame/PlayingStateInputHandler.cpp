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

   bool isLeftDown = _inputReader->IsButtonDown( Button::Left );
   bool isRightDown = _inputReader->IsButtonDown( Button::Right );

   if ( isLeftDown && !isRightDown )
   {
      auto ball = _gameData->GetBall();
      auto newAngle = ball->GetAngle() + ( _gameConfig->TurnAngleIncrement * _clock->GetFrameSeconds() );
      NORMALIZE_ANGLE( newAngle );
      _gameData->GetBall()->SetAngle( newAngle );
   }
   else if ( isRightDown && !isLeftDown )
   {
      auto ball = _gameData->GetBall();
      auto newAngle = ball->GetAngle() - ( _gameConfig->TurnAngleIncrement * _clock->GetFrameSeconds() );
      NORMALIZE_ANGLE( newAngle );
      _gameData->GetBall()->SetAngle( newAngle );
   }
}

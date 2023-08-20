#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameClock.h"
#include "EventAggregator.h"
#include "Entity.h"
#include "Geometry.h"
#include "TurnBallArgs.h"
#include "PushBallArgs.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<GameData> gameData,
                                                    shared_ptr<GameClock> clock,
                                                    shared_ptr<EventAggregator> eventAggregator ) :
   _inputReader( inputReader ),
   _gameConfig( gameConfig ),
   _gameData( gameData ),
   _clock( clock ),
   _eventAggregator( eventAggregator )
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
      _eventAggregator->PushEvent( { GameEventType::TurnBall, shared_ptr<TurnBallArgs>( new TurnBallArgs( _gameConfig->BallTurnAngleIncrement ) ) } );
   }
   else if ( isRightDown && !isLeftDown )
   {
      _eventAggregator->PushEvent( { GameEventType::TurnBall, shared_ptr<TurnBallArgs>( new TurnBallArgs( -( _gameConfig->BallTurnAngleIncrement ) ) ) } );
   }

   bool isForwardDown = _inputReader->IsButtonDown( Button::Up );
   bool isBackwardDown = _inputReader->IsButtonDown( Button::Down );

   if ( isForwardDown && !isBackwardDown )
   {
      _eventAggregator->PushEvent( { GameEventType::PushBall, shared_ptr<PushBallArgs>( new PushBallArgs( _gameConfig->BallVelocityIncrement ) ) } );
   }
   else if ( isBackwardDown && !isForwardDown )
   {
      _eventAggregator->PushEvent( { GameEventType::PushBall, shared_ptr<PushBallArgs>( new PushBallArgs( -_gameConfig->BallVelocityIncrement ) ) } );
   }
}

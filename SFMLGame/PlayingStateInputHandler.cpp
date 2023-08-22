#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameConfig.h"
#include "EventQueue.h"
#include "Entity.h"
#include "Geometry.h"
#include "TurnBallArgs.h"
#include "PushBallArgs.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<EventQueue> eventQueue ) :
   _inputReader( inputReader ),
   _gameConfig( gameConfig ),
   _eventQueue( eventQueue )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _eventQueue->Push( GameEventType::OpenMenu );
      return;
   }

   bool isLeftDown = _inputReader->IsButtonDown( Button::Left );
   bool isRightDown = _inputReader->IsButtonDown( Button::Right );

   if ( isLeftDown && !isRightDown )
   {
      _eventQueue->Push( GameEventType::TurnBall, shared_ptr<TurnBallArgs>( new TurnBallArgs( _gameConfig->BallTurnAngleIncrement ) ) );
   }
   else if ( isRightDown && !isLeftDown )
   {
      _eventQueue->Push( GameEventType::TurnBall, shared_ptr<TurnBallArgs>( new TurnBallArgs( -( _gameConfig->BallTurnAngleIncrement ) ) ) );
   }

   bool isForwardDown = _inputReader->IsButtonDown( Button::Up );
   bool isBackwardDown = _inputReader->IsButtonDown( Button::Down );

   if ( isForwardDown && !isBackwardDown )
   {
      _eventQueue->Push( GameEventType::PushBall, shared_ptr<PushBallArgs>( new PushBallArgs( _gameConfig->BallVelocityIncrement ) ) );
   }
   else if ( isBackwardDown && !isForwardDown )
   {
      _eventQueue->Push( GameEventType::PushBall, shared_ptr<PushBallArgs>( new PushBallArgs( -_gameConfig->BallVelocityIncrement ) ) );
   }
}

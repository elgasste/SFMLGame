#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameConfig.h"
#include "EventQueue.h"
#include "Entity.h"
#include "Geometry.h"
#include "TurnPlayerArgs.h"
#include "MovePlayerArgs.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<InputReader> inputReader,
                                                    shared_ptr<GameConfig> gameConfig,
                                                    shared_ptr<EventQueue> eventQueue ) :
   _inputReader( inputReader ),
   _gameConfig( gameConfig ),
   _eventQueue( eventQueue ),
   _isLeftDown( false ),
   _isUpDown( false ),
   _isRightDown( false ),
   _isDownDown( false ),
   _directionWasPressedLastFrame( false ),
   _directionCache( (Direction)0 )
{
}

void PlayingStateInputHandler::HandleInput()
{
   if ( _inputReader->WasButtonPressed( Button::Back ) )
   {
      _eventQueue->Push( GameEventType::OpenMenu );
      return;
   }

   CacheDirectionInput();

   if ( _isLeftDown && !_isRightDown )
   {
      auto velocity = ( ( _isUpDown && !_isDownDown ) || ( _isDownDown && !_isUpDown ) )
         ? _gameConfig->PlayerVelocityIncrement * _gameConfig->PlayerVelocityDiagonalScalar
         : _gameConfig->PlayerVelocityIncrement;
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Left, velocity ) ) );
   }
   else if ( _isRightDown && !_isLeftDown )
   {
      auto velocity = ( ( _isUpDown && !_isDownDown ) || ( _isDownDown && !_isUpDown ) )
         ? _gameConfig->PlayerVelocityIncrement * _gameConfig->PlayerVelocityDiagonalScalar
         : _gameConfig->PlayerVelocityIncrement;
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Right, velocity ) ) );
   }

   if ( _isUpDown && !_isDownDown )
   {
      auto velocity = ( ( _isLeftDown && !_isRightDown ) || ( _isRightDown && !_isLeftDown ) )
         ? _gameConfig->PlayerVelocityIncrement * _gameConfig->PlayerVelocityDiagonalScalar
         : _gameConfig->PlayerVelocityIncrement;
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Up, velocity ) ) );
   }
   else if ( _isDownDown && !_isUpDown )
   {
      auto velocity = ( ( _isLeftDown && !_isRightDown ) || ( _isRightDown && !_isLeftDown ) )
         ? _gameConfig->PlayerVelocityIncrement * _gameConfig->PlayerVelocityDiagonalScalar
         : _gameConfig->PlayerVelocityIncrement;
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Down, velocity ) ) );
   }
}

void PlayingStateInputHandler::CacheDirectionInput()
{
   _isLeftDown = _inputReader->IsButtonDown( Button::Left );
   _isUpDown = _inputReader->IsButtonDown( Button::Up );
   _isRightDown = _inputReader->IsButtonDown( Button::Right );
   _isDownDown = _inputReader->IsButtonDown( Button::Down );

   bool directionWasPressed = _isLeftDown || _isUpDown || _isRightDown || _isDownDown;

   if ( !directionWasPressed )
   {
      _directionWasPressedLastFrame = false;
      return;
   }

   if ( !_directionWasPressedLastFrame )
   {
      _directionWasPressedLastFrame = true;

      if ( _isLeftDown )
      {
         _directionCache = Direction::Left;
         _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Left ) ) );
      }
      else if ( _isUpDown )
      {
         _directionCache = Direction::Up;
         _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Up ) ) );
      }
      else if ( _isRightDown )
      {
         _directionCache = Direction::Right;
         _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Right ) ) );
      }
      else if ( _isDownDown )
      {
         _directionCache = Direction::Down;
         _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Down ) ) );
      }
   }
   else
   {
      if ( _directionCache == Direction::Left && !_isLeftDown )
      {
         if ( _isUpDown && !_isDownDown )
         {
            _directionCache = Direction::Up;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Up ) ) );
         }
         else if ( _isRightDown )
         {
            _directionCache = Direction::Right;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Right ) ) );
         }
         else if ( _isDownDown && !_isUpDown )
         {
            _directionCache = Direction::Down;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Down ) ) );
         }
      }
      else if ( _directionCache == Direction::Up && !_isUpDown )
      {
         if ( _isRightDown && !_isLeftDown )
         {
            _directionCache = Direction::Right;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Right ) ) );
         }
         else if ( _isDownDown )
         {
            _directionCache = Direction::Down;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Down ) ) );
         }
         else if ( _isLeftDown && !_isRightDown )
         {
            _directionCache = Direction::Left;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Left ) ) );
         }
      }
      else if ( _directionCache == Direction::Right && !_isRightDown )
      {
         if ( _isDownDown && !_isUpDown )
         {
            _directionCache = Direction::Down;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Down ) ) );
         }
         else if ( _isLeftDown )
         {
            _directionCache = Direction::Left;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Left ) ) );
         }
         else if ( _isUpDown && !_isDownDown )
         {
            _directionCache = Direction::Up;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Up ) ) );
         }
      }
      else if ( _directionCache == Direction::Down && !_isDownDown )
      {
         if ( _isLeftDown && !_isRightDown )
         {
            _directionCache = Direction::Left;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Left ) ) );
         }
         else if ( _isUpDown )
         {
            _directionCache = Direction::Up;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Up ) ) );
         }
         else if ( _isRightDown && !_isLeftDown )
         {
            _directionCache = Direction::Right;
            _eventQueue->Push( GameEventType::TurnPlayer, shared_ptr<TurnPlayerArgs>( new TurnPlayerArgs( Direction::Right ) ) );
         }
      }
   }
}

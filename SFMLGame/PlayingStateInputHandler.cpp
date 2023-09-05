#include "PlayingStateInputHandler.h"
#include "InputReader.h"
#include "GameConfig.h"
#include "EventQueue.h"
#include "Entity.h"
#include "Geometry.h"
#include "MovePlayerArgs.h"

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
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Left ) ) );
   }
   else if ( isRightDown && !isLeftDown )
   {
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Right ) ) );
   }

   bool isUpDown = _inputReader->IsButtonDown( Button::Up );
   bool isDownDown = _inputReader->IsButtonDown( Button::Down );

   if ( isUpDown && !isDownDown )
   {
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Up ) ) );
   }
   else if ( isDownDown && !isUpDown )
   {
      _eventQueue->Push( GameEventType::MovePlayer, shared_ptr<MovePlayerArgs>( new MovePlayerArgs( Direction::Down ) ) );
   }
}

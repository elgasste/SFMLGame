#include "ArenaInputHandler.h"
#include "GameData.h"
#include "CommandAggregator.h"
#include "IInputReader.h"
#include "GameCommand.h"

using namespace NAMESPACE;
using namespace std;

ArenaInputHandler::ArenaInputHandler( shared_ptr<CommandAggregator> commandAggregator,
                                      shared_ptr<IInputReader> inputReader ) :
   _commandAggregator( commandAggregator ),
   _inputReader( inputReader )
{
}

void ArenaInputHandler::HandleInput() const
{
   if ( _inputReader->IsButtonDown( Button::Left ) && !_inputReader->IsButtonDown( Button::Right ) )
   {
      auto direction = Direction::Left;
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&direction );
   }
   else if ( _inputReader->IsButtonDown( Button::Right ) && !_inputReader->IsButtonDown( Button::Left ) )
   {
      auto direction = Direction::Right;
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&direction );
   }
   else
   {
      _commandAggregator->ExecuteCommand( GameCommand::StopPlayerX, nullptr );
   }

   if ( _inputReader->IsButtonDown( Button::Up ) && !_inputReader->IsButtonDown( Button::Down ) )
   {
      auto direction = Direction::Up;
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&direction );
   }
   else if ( _inputReader->IsButtonDown( Button::Down ) && !_inputReader->IsButtonDown( Button::Up ) )
   {
      auto direction = Direction::Down;
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&direction );
   }
   else
   {
      _commandAggregator->ExecuteCommand( GameCommand::StopPlayerY, nullptr );
   }
}

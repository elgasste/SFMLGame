#include "PlayingStateInputHandler.h"
#include "GameData.h"
#include "CommandAggregator.h"
#include "IInputReader.h"
#include "GameCommand.h"
#include "MovePlayerCommandArgs.h"

using namespace NAMESPACE;
using namespace std;

PlayingStateInputHandler::PlayingStateInputHandler( shared_ptr<GameData> gameData,
                                                    shared_ptr<CommandAggregator> commandAggregator,
                                                    shared_ptr<IInputReader> inputReader ) :
   _gameData( gameData ),
   _commandAggregator( commandAggregator ),
   _inputReader( inputReader )
{
}

void PlayingStateInputHandler::HandleInput()
{
   auto left = _inputReader->IsButtonDown( Button::Left );
   auto up = _inputReader->IsButtonDown( Button::Up );
   auto right = _inputReader->IsButtonDown( Button::Right );
   auto down = _inputReader->IsButtonDown( Button::Down );

   if ( left && !right )
   {
      auto velocity = ( up || down ) ? _gameData->PlayerMoveVelocity * 0.75f : _gameData->PlayerMoveVelocity;
      auto args = MovePlayerCommandArgs{ Direction::Left, velocity };
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&args );
   }
   else if ( right && !left )
   {
      auto velocity = ( up || down ) ? _gameData->PlayerMoveVelocity * 0.75f : _gameData->PlayerMoveVelocity;
      auto args = MovePlayerCommandArgs{ Direction::Right, velocity };
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&args );
   }
   else
   {
      _commandAggregator->ExecuteCommand( GameCommand::StopPlayerX, nullptr );
   }

   if ( up && !down )
   {
      auto velocity = ( left || right ) ? _gameData->PlayerMoveVelocity * 0.75f : _gameData->PlayerMoveVelocity;
      auto args = MovePlayerCommandArgs{ Direction::Up, velocity };
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&args );
   }
   else if ( down && !up )
   {
      auto velocity = ( left || right ) ? _gameData->PlayerMoveVelocity * 0.75f : _gameData->PlayerMoveVelocity;
      auto args = MovePlayerCommandArgs{ Direction::Down, velocity };
      _commandAggregator->ExecuteCommand( GameCommand::MovePlayer, (void*)&args );
   }
   else
   {
      _commandAggregator->ExecuteCommand( GameCommand::StopPlayerY, nullptr );
   }
}

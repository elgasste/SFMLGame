#include "GameLogic.h"
#include "GameInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( std::shared_ptr<GameInputHandler> inputHandler,
                      std::shared_ptr<Entity> player ) :
   _inputHandler( inputHandler ),
   _player( player )
{
   // MUFFINS: does it make sense for this class to hold onto the player entity?
   // maybe that should go in GameData or some other class that keeps all the game objects?
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   // TODO: update the game data
}

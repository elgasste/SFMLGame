#include "GameLogic.h"
#include "GameInputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameInputHandler> inputHandler ) :
   _inputHandler( inputHandler )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   // TODO: update the game data
}

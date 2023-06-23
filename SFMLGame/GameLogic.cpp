#include "GameLogic.h"
#include "InputHandler.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( std::shared_ptr<InputHandler> inputHandler ) :
   _inputHandler( inputHandler )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   // TODO: update the game data
}

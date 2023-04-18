#include "GameLogic.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "GameInputHandler.h"
#include "Arena.h"
#include "Player.h"

using namespace NAMESPACE;
using namespace std;

GameLogic::GameLogic( shared_ptr<GameConfig> config,
                      shared_ptr<EventAggregator> eventAggregator,
                      shared_ptr<GameInputHandler> inputHandler,
                      shared_ptr<Arena> arena ) :
   _config( config ),
   _eventAggregator( eventAggregator ),
   _inputHandler( inputHandler ),
   _arena( arena )
{
}

void GameLogic::Tick()
{
   _inputHandler->HandleInput();

   _arena->Tick();
}

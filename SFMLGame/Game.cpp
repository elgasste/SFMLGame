#include "Game.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameLogic.h"
#include "GameRenderer.h"

using namespace NAMESPACE;
using namespace std;

Game::Game( shared_ptr<GameClock> clock,
            shared_ptr<InputReader> inputReader,
            shared_ptr<GameLogic> logic,
            shared_ptr<GameRenderer> renderer,
            shared_ptr<GameRunningTracker> gameRunningTracker,
            shared_ptr<GameStateTracker> gameStateTracker ) :
   _clock( clock ),
   _inputReader( inputReader ),
   _logic( logic ),
   _renderer( renderer ),
   _gameRunningTracker( gameRunningTracker ),
   _gameStateTracker( gameStateTracker )
{
}

void Game::Run()
{
   if ( _gameRunningTracker->isRunning )
   {
      return;
   }

   _gameRunningTracker->isRunning = true;

   _renderer->Initialize();
   _clock->Initialize();

   while ( _gameRunningTracker->isRunning )
   {
      _clock->StartFrame();

      _inputReader->ReadInput();
      _logic->Tick();
      _renderer->Render();

      _clock->EndFrame();
   }
}

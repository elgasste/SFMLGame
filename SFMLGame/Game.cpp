#include "Game.h"
#include "GameClock.h"
#include "InputHandler.h"
#include "GameLogic.h"
#include "SFMLWindow.h"
#include "GameRenderer.h"

using namespace NAMESPACE;
using namespace std;

Game::Game( shared_ptr<GameClock> clock,
            shared_ptr<InputHandler> inputHandler,
            shared_ptr<GameLogic> logic,
            shared_ptr<SFMLWindow> window,
            shared_ptr<GameRenderer> renderer,
            shared_ptr<GameRunningTracker> gameRunningTracker,
            shared_ptr<GameStateTracker> gameStateTracker ) :
   _clock( clock ),
   _logic( logic ),
   _inputHandler( inputHandler ),
   _window( window ),
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

   while ( _gameRunningTracker->isRunning )
   {
      _clock->StartFrame();

      _window->HandleEvents();
      _logic->Tick();
      _renderer->Render();

      _clock->EndFrame();
   }
}

#include "Game.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "SFMLWindow.h"

using namespace NAMESPACE;
using namespace std;

Game::Game( shared_ptr<GameClock> clock,
            shared_ptr<InputReader> inputReader,
            shared_ptr<GameInputHandler> inputHandler,
            shared_ptr<GameLogic> logic,
            shared_ptr<GameRenderer> renderer,
            shared_ptr<SFMLWindow> window,
            shared_ptr<GameRunningTracker> gameRunningTracker,
            shared_ptr<GameStateTracker> gameStateTracker ) :
   _clock( clock ),
   _inputReader( inputReader ),
   _inputHandler( inputHandler ),
   _logic( logic ),
   _renderer( renderer ),
   _window( window ),
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

      _window->HandleEvents();
      _inputHandler->HandleInput();
      _logic->Tick();
      _renderer->Render();

      _clock->EndFrame();
   }
}

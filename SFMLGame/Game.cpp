#include "Game.h"
#include "GameData.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameLogic.h"
#include "GameRenderer.h"

using namespace NAMESPACE;
using namespace std;

Game::Game( shared_ptr<GameData> gameData,
            shared_ptr<EventAggregator> eventAggregator,
            shared_ptr<GameClock> clock,
            shared_ptr<InputReader> inputReader,
            shared_ptr<GameLogic> logic,
            shared_ptr<GameRenderer> renderer ) :
   _gameData( gameData ),
   _eventAggregator( eventAggregator ),
   _clock( clock ),
   _inputReader( inputReader ),
   _logic( logic ),
   _renderer( renderer ),
   _isRunning( false )
{
   _eventAggregator->AddListener( GameEvent::Quit, this );
}

void Game::Run()
{
   if ( _isRunning )
   {
      return;
   }

   _isRunning = true;

   _renderer->Initialize();
   _clock->Initialize();

   while ( _isRunning )
   {
      _clock->StartFrame();

      _inputReader->ReadInput();
      _logic->Tick();
      _renderer->Render();

      _clock->EndFrame();
   }
}

void Game::HandleEvent( GameEvent event )
{
   if ( event == GameEvent::Quit )
   {
      _isRunning = false;
   }
}

#include "GameLoader.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "SFMLWindow.h"
#include "GameRenderer.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;

shared_ptr<Game> GameLoader::Load()
{
   auto config = make_shared<GameConfig>();
   auto eventAggregator = make_shared<EventAggregator>();
   auto clock = shared_ptr<GameClock>( new GameClock( config ) );
   auto inputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( config ) );
   auto logic = shared_ptr<GameLogic>( new GameLogic( config, eventAggregator, inputReader ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( config, eventAggregator, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( config, clock, window ) );
   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( config, window, diagnosticRenderer ) );
   auto game = shared_ptr<Game>( new Game( eventAggregator, clock, inputReader, logic, renderer ) );

   return game;
}

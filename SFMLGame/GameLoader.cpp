#include "GameLoader.h"
#include "GameConfig.h"
#include "GameData.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "Player.h"
#include "Arena.h"
#include "ArenaInputHandler.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "ArenaRenderer.h"
#include "SFMLWindow.h"
#include "GameRenderer.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;

shared_ptr<Game> GameLoader::Load()
{
   auto config = make_shared<GameConfig>();
   auto gameData = shared_ptr<GameData>( new GameData( config ) );
   auto eventAggregator = make_shared<EventAggregator>();
   auto clock = shared_ptr<GameClock>( new GameClock( config ) );
   auto inputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( config ) );
   auto player = shared_ptr<Player>( new Player( gameData ) );
   auto arena = shared_ptr<Arena>( new Arena( gameData, clock, player ) );
   auto arenaInputHandler = shared_ptr<ArenaInputHandler>( new ArenaInputHandler( gameData, inputReader, arena ) );
   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( config, inputReader, eventAggregator, arenaInputHandler ) );
   auto logic = shared_ptr<GameLogic>( new GameLogic( config, eventAggregator, inputHandler, arena ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( config, eventAggregator, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( config, clock, window ) );
   auto arenaRenderer = shared_ptr<ArenaRenderer>( new ArenaRenderer( config, window, arena ) );
   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( config, window, diagnosticRenderer, arenaRenderer ) );
   auto game = shared_ptr<Game>( new Game( eventAggregator, clock, inputReader, logic, renderer ) );

   return game;
}

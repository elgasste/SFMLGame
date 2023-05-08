#include <fstream>
#include <sstream>

#include "GameLoader.h"
#include "UniqueNumberGenerator.h"
#include "Random.h"
#include "GameConfig.h"
#include "GameData.h"
#include "GameStateProvider.h"
#include "RenderData.h"
#include "EventAggregator.h"
#include "CommandAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "Player.h"
#include "Actor.h"
#include "Arena.h"
#include "Behavior.h"
#include "MbcAsmCompiler.h"
#include "LoadingStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "LoadingStateRenderer.h"
#include "PlayingStateRenderer.h"
#include "SFMLWindow.h"
#include "GameRenderer.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;

shared_ptr<Game> GameLoader::Load()
{
   auto uniqueNumberGenerator = make_shared<UniqueNumberGenerator>();
   auto random = make_shared<Random>();
   auto config = make_shared<GameConfig>();
   auto gameData = shared_ptr<GameData>( new GameData( config, uniqueNumberGenerator ) );
   auto gameStateProvider = make_shared<GameStateProvider>();
   auto eventAggregator = make_shared<EventAggregator>();
   auto commandAggregator = make_shared<CommandAggregator>();
   auto clock = shared_ptr<GameClock>( new GameClock( config ) );
   auto inputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( config ) );
   auto player = shared_ptr<Player>( new Player( uniqueNumberGenerator, gameData ) );
   auto arena = shared_ptr<Arena>( new Arena( gameData, clock, player ) );

   auto mbcCompiler = make_shared<MbcAsmCompiler>();
   ifstream asmStream( "mbcasm/npc.mbcasm" );
   stringstream asmBuffer;
   asmBuffer << asmStream.rdbuf();
   auto mbc = mbcCompiler->Compile( asmBuffer.str() );
   auto npcBehavior = shared_ptr<Behavior>( new Behavior( clock, random, player ) );
   npcBehavior->SetInstructions( mbc );
   npcBehavior->SetEntity( gameData->Npc );
   gameData->Npc->SetBehavior( npcBehavior );

   auto loadingStateInputHandler = make_shared<LoadingStateInputHandler>();
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( gameData, commandAggregator, inputReader ) );
   auto gameStateInputHandlers = map<GameState, shared_ptr<IGameStateInputHandler>>
   {
      { GameState::Loading, loadingStateInputHandler },
      { GameState::Playing, playingStateInputHandler }
   };

   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( config, inputReader, eventAggregator, gameStateInputHandlers, gameStateProvider ) );
   auto logic = shared_ptr<GameLogic>( new GameLogic( config, gameData, gameStateProvider, eventAggregator, commandAggregator, inputHandler, arena ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( config, eventAggregator, clock ) );
   auto renderData = shared_ptr<RenderData>( new RenderData( clock, player, gameData->Npc ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( config, clock, window ) );

   auto loadingStateRenderer = shared_ptr<LoadingStateRenderer>( new LoadingStateRenderer( config, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( renderData, window ) );
   auto gameStateRenderers = map<GameState, shared_ptr<IGameStateRenderer>>
   {
      { GameState::Loading, loadingStateRenderer },
      { GameState::Playing, playingStateRenderer }
   };

   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( config, gameStateProvider, window, diagnosticRenderer, gameStateRenderers ) );
   auto game = shared_ptr<Game>( new Game( eventAggregator, clock, inputReader, logic, renderer ) );

   return game;
}

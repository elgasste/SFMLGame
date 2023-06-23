#include "GameLoader.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "GameStateController.h"
#include "PlayingStateInputHandler.h"
#include "InputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "PlayingStateRenderer.h"
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
   auto stateController = make_shared<GameStateController>();
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, eventAggregator ) );
   auto inputHandler = shared_ptr<InputHandler>( new InputHandler( config, inputReader, stateController ) );
   inputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   auto logic = shared_ptr<GameLogic>( new GameLogic( inputHandler ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( config, eventAggregator, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( config, clock, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer() );
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( config, window, diagnosticRenderer, stateController ) );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   auto game = shared_ptr<Game>( new Game( eventAggregator, clock, inputReader, logic, gameRenderer ) );

   return game;
}

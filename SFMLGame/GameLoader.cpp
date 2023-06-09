#include "GameLoader.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "GameStateController.h"
#include "BackMenuOption.h"
#include "QuitMenuOption.h"
#include "Menu.h"
#include "PlayingStateInputHandler.h"
#include "MenuStateInputHandler.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "PlayingStateRenderer.h"
#include "MenuStateRenderer.h"
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
   auto backMenuOption = shared_ptr<BackMenuOption>( new BackMenuOption( stateController ) );
   auto quitMenuOption = shared_ptr<QuitMenuOption>( new QuitMenuOption( eventAggregator ) );
   auto menu = make_shared<Menu>();
   menu->AddOption( backMenuOption );
   menu->AddOption( quitMenuOption );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, stateController ) );
   auto menuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, stateController, menu ) );
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( config, inputReader, stateController ) );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Menu, menuStateInputHandler );
   auto logic = shared_ptr<GameLogic>( new GameLogic( gameInputHandler ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( config, eventAggregator, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( config, clock, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( config, window ) );
   auto menuStateRenderer = shared_ptr<MenuStateRenderer>( new MenuStateRenderer( config, window, clock, menu ) );
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( config, window, diagnosticRenderer, stateController ) );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Menu, menuStateRenderer );
   auto game = shared_ptr<Game>( new Game( eventAggregator, clock, inputReader, logic, gameRenderer ) );

   return game;
}

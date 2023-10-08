#include "GameLoader.h"
#include "GameConfig.h"
#include "Entity.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "InputReader.h"
#include "TitleMenu.h"
#include "MainMenu.h"
#include "MenuStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "ClosingStateInputHandler.h"
#include "InputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "TitleMenuStateRenderer.h"
#include "PlayingStateRenderer.h"
#include "MainMenuStateRenderer.h"
#include "ClosingStateRenderer.h"
#include "SFMLWindow.h"
#include "GameRenderer.h"
#include "Game.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

shared_ptr<Game> GameLoader::Load() const
{
   auto gameConfig = make_shared<GameConfig>();
   auto gameData = LoadGameData( gameConfig );
   auto renderConfig = make_shared<RenderConfig>();
   auto renderData = LoadRenderData();
   auto gameRunningTracker = make_shared<GameRunningTracker>();
   auto gameStateTracker = make_shared<GameStateTracker>();
   auto eventQueue = make_shared<EventQueue>();
   auto clock = shared_ptr<GameClock>( new GameClock( renderConfig ) );
   auto inputReader = shared_ptr<InputReader>( new InputReader( gameConfig ) );
   auto titleMenu = shared_ptr<TitleMenu>( new TitleMenu( eventQueue ) );
   auto mainMenu = shared_ptr<MainMenu>( new MainMenu( eventQueue ) );
   auto titleMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, eventQueue, titleMenu ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, gameConfig, eventQueue ) );
   auto mainMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, eventQueue, mainMenu ) );
   auto closingStateInputHandler = make_shared<ClosingStateInputHandler>();
   auto gameInputHandler = shared_ptr<InputHandler>( new InputHandler( gameConfig, inputReader, gameStateTracker ) );
   gameInputHandler->AddStateInputHandler( GameState::TitleMenu, titleMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::MainMenu, mainMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Closing, closingStateInputHandler );
   auto gameLogic = shared_ptr<GameLogic>( new GameLogic( gameConfig, gameData, renderConfig, eventQueue, clock, gameRunningTracker, gameStateTracker ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( renderConfig, clock, inputReader, gameInputHandler ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, gameData, clock, window ) );
   auto titleMenuStateRenderer = shared_ptr<TitleMenuStateRenderer>( new TitleMenuStateRenderer( renderConfig, window, clock, titleMenu ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( renderConfig, renderData, gameConfig, gameData, window ) );
   auto mainMenuStateRenderer = shared_ptr<MainMenuStateRenderer>( new MainMenuStateRenderer( gameConfig, gameData, renderConfig, renderData, window, clock, mainMenu ) );
   auto closingStateRenderer = make_shared<ClosingStateRenderer>();
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( renderData, gameConfig, window, diagnosticRenderer, gameStateTracker ) );
   gameRenderer->AddStateRenderer( GameState::TitleMenu, titleMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::MainMenu, mainMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Closing, closingStateRenderer );
   auto game = shared_ptr<Game>( new Game( clock, gameInputHandler, gameLogic, window, gameRenderer, gameRunningTracker, gameStateTracker ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto ball = make_shared<Entity>();
   ball->SetHitBoxDimensions( gameConfig->BallDiameter, gameConfig->BallDiameter );

   auto gameData = shared_ptr<GameData>( new GameData( ball ) );

   return gameData;
}

shared_ptr<RenderData> GameLoader::LoadRenderData() const
{
   auto ballTexture = shared_ptr<Texture>( new Texture() );
   ballTexture->loadFromFile( "Resources/Textures/ball.png" );

   auto renderData = shared_ptr<RenderData>( new RenderData( ballTexture ) );

   return renderData;
}

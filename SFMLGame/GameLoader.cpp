#include "GameLoader.h"
#include "GameConfig.h"
#include "Entity.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "InputReader.h"
#include "PlayingStateMenu.h"
#include "PlayingStateInputHandler.h"
#include "MenuStateInputHandler.h"
#include "ClosingStateInputHandler.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "PlayingStateRenderer.h"
#include "MenuStateRenderer.h"
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
   auto playingStateMenu = shared_ptr<PlayingStateMenu>( new PlayingStateMenu( eventQueue ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, gameConfig, eventQueue ) );
   auto menuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, eventQueue, playingStateMenu ) );
   auto closingStateInputHandler = make_shared<ClosingStateInputHandler>();
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( gameConfig, inputReader, gameStateTracker ) );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Menu, menuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Closing, closingStateInputHandler );
   auto gameLogic = shared_ptr<GameLogic>( new GameLogic( gameConfig, gameData, renderConfig, gameInputHandler, eventQueue, clock, gameRunningTracker, gameStateTracker ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( renderConfig, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, gameData, clock, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( renderConfig, renderData, gameConfig, gameData, window ) );
   auto menuStateRenderer = shared_ptr<MenuStateRenderer>( new MenuStateRenderer( renderConfig, window, clock, playingStateMenu ) );
   auto closingStateRenderer = make_shared<ClosingStateRenderer>();
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( renderData, gameConfig, window, diagnosticRenderer, gameStateTracker ) );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Menu, menuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Closing, closingStateRenderer );
   auto game = shared_ptr<Game>( new Game( clock, inputReader, gameLogic, gameRenderer, gameRunningTracker, gameStateTracker ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto ball = make_shared<Entity>();
   ball->SetHitBoxDimensions( gameConfig->BallDiameter, gameConfig->BallDiameter );
   ball->SetPosition( gameConfig->DefaultBallPosition.x, gameConfig->DefaultBallPosition.y );
   ball->SetAngle( gameConfig->DefaultBallAngle );
   ball->SetVelocity( gameConfig->DefaultBallVelocity );

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

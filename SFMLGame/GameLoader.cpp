#include "GameLoader.h"
#include "GameConfig.h"
#include "Entity.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "RenderData.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "InputReader.h"
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
using namespace sf;

shared_ptr<Game> GameLoader::Load() const
{
   auto gameConfig = make_shared<GameConfig>();
   auto gameData = LoadGameData( gameConfig );
   auto renderConfig = make_shared<RenderConfig>();
   auto renderData = LoadRenderData();
   auto eventAggregator = make_shared<EventAggregator>();
   auto clock = shared_ptr<GameClock>( new GameClock( renderConfig ) );
   auto inputReader = shared_ptr<InputReader>( new InputReader( gameConfig ) );
   auto backMenuOption = shared_ptr<BackMenuOption>( new BackMenuOption( gameData ) );
   auto quitMenuOption = shared_ptr<QuitMenuOption>( new QuitMenuOption( eventAggregator ) );
   auto menu = make_shared<Menu>();
   menu->AddOption( backMenuOption );
   menu->AddOption( quitMenuOption );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, gameData ) );
   auto menuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, gameData, menu ) );
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( gameConfig, gameData, inputReader ) );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Menu, menuStateInputHandler );
   auto logic = shared_ptr<GameLogic>( new GameLogic( gameInputHandler ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( renderConfig, eventAggregator, clock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, clock, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( renderConfig, renderData, window ) );
   auto menuStateRenderer = shared_ptr<MenuStateRenderer>( new MenuStateRenderer( renderConfig, window, clock, menu ) );
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( gameConfig, gameData, window, diagnosticRenderer ) );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Menu, menuStateRenderer );
   auto game = shared_ptr<Game>( new Game( gameData, eventAggregator, clock, inputReader, logic, gameRenderer ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto ball = make_shared<Entity>();
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

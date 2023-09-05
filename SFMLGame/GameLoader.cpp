#include "GameLoader.h"
#include "GameConfig.h"
#include "Entity.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "EntitySprite.h"
#include "RenderData.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "InputReader.h"
#include "TitleMenu.h"
#include "MainMenu.h"
#include "MenuStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "ClosingStateInputHandler.h"
#include "GameInputHandler.h"
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
   auto gameClock = shared_ptr<GameClock>( new GameClock( renderConfig ) );
   auto renderData = LoadRenderData( renderConfig, gameData, gameClock );
   auto gameRunningTracker = make_shared<GameRunningTracker>();
   auto gameStateTracker = make_shared<GameStateTracker>();
   auto eventQueue = make_shared<EventQueue>();
   auto inputReader = shared_ptr<InputReader>( new InputReader( gameConfig ) );
   auto titleMenu = shared_ptr<TitleMenu>( new TitleMenu( eventQueue ) );
   auto mainMenu = shared_ptr<MainMenu>( new MainMenu( eventQueue ) );
   auto titleMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, eventQueue, titleMenu ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, gameConfig, eventQueue ) );
   auto mainMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, eventQueue, mainMenu ) );
   auto closingStateInputHandler = make_shared<ClosingStateInputHandler>();
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( gameConfig, inputReader, gameStateTracker ) );
   gameInputHandler->AddStateInputHandler( GameState::TitleMenu, titleMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::MainMenu, mainMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Closing, closingStateInputHandler );
   auto gameLogic = shared_ptr<GameLogic>( new GameLogic( gameConfig, gameData, renderConfig, gameInputHandler, eventQueue, gameClock, gameRunningTracker, gameStateTracker ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( renderConfig, gameClock ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, gameClock, window ) );
   auto titleMenuStateRenderer = shared_ptr<TitleMenuStateRenderer>( new TitleMenuStateRenderer( renderConfig, window, gameClock, titleMenu ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( renderConfig, renderData, gameConfig, gameData, window ) );
   auto mainMenuStateRenderer = shared_ptr<MainMenuStateRenderer>( new MainMenuStateRenderer( renderConfig, window, gameClock, mainMenu ) );
   auto closingStateRenderer = make_shared<ClosingStateRenderer>();
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( renderData, gameConfig, window, diagnosticRenderer, gameStateTracker ) );
   gameRenderer->AddStateRenderer( GameState::TitleMenu, titleMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::MainMenu, mainMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Closing, closingStateRenderer );
   auto game = shared_ptr<Game>( new Game( gameClock, inputReader, gameLogic, gameRenderer, gameRunningTracker, gameStateTracker ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto player = make_shared<Entity>();
   player->SetHitBoxDimensions( gameConfig->PlayerHitBoxWidth, gameConfig->PlayerHitBoxHeight );

   auto gameData = shared_ptr<GameData>( new GameData( player ) );

   return gameData;
}

shared_ptr<RenderData> GameLoader::LoadRenderData( shared_ptr<RenderConfig> renderConfig,
                                                   shared_ptr<GameData> gameData,
                                                   shared_ptr<GameClock> gameClock ) const
{
   auto playerSpriteTexture = shared_ptr<Texture>( new Texture() );
   playerSpriteTexture->loadFromFile( "Resources/Textures/BODY_male.png" );

   auto playerSprite = shared_ptr<EntitySprite>( new EntitySprite( renderConfig,
                                                                   gameClock,
                                                                   gameData->GetPlayer(),
                                                                   playerSpriteTexture,
                                                                   renderConfig->PlayerSpriteSize,
                                                                   renderConfig->PlayerSpriteOrigin,
                                                                   renderConfig->PlayerSpriteMovementFrames ) );

   auto renderData = make_shared<RenderData>();
   renderData->SetPlayerSpriteTexture( playerSpriteTexture );
   renderData->SetPlayerSprite( playerSprite );

   return renderData;
}

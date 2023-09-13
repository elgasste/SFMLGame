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
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( gameConfig, window, diagnosticRenderer, gameStateTracker ) );
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
   player->SetHitBoxSize( gameConfig->PlayerHitBoxWidth, gameConfig->PlayerHitBoxHeight );
   player->SetHitBoxOffset( -( gameConfig->PlayerHitBoxWidth / 2.0f ), -( gameConfig->PlayerHitBoxHeight / 2.0f ) );

   auto gameData = shared_ptr<GameData>( new GameData( LoadLinedefs(), LoadBspTree(), player ) );

   return gameData;
}

shared_ptr<RenderData> GameLoader::LoadRenderData( shared_ptr<RenderConfig> renderConfig,
                                                   shared_ptr<GameData> gameData,
                                                   shared_ptr<GameClock> gameClock ) const
{
   auto playerSpriteTextureLayerMap = make_shared<map<EntitySpriteLayer, shared_ptr<Texture>>>();
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Body] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Body )->loadFromFile( "Resources/Textures/BODY_male.png" );
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Legs] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Legs )->loadFromFile( "Resources/Textures/LEGS_pants_greenish.png" );
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Torso] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Torso )->loadFromFile( "Resources/Textures/TORSO_leather_armor.png" );
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Belt] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Belt )->loadFromFile( "Resources/Textures/BELT_leather.png" );
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Feet] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Feet )->loadFromFile( "Resources/Textures/FEET_shoes_brown.png" );
   ( *playerSpriteTextureLayerMap )[EntitySpriteLayer::Head] = shared_ptr<Texture>( new Texture() );
   playerSpriteTextureLayerMap->at( EntitySpriteLayer::Head )->loadFromFile( "Resources/Textures/HEAD_leather_armor_hat.png" );

   auto playerSprite = shared_ptr<EntitySprite>( new EntitySprite( renderConfig,
                                                                   gameClock,
                                                                   gameData->GetPlayer(),
                                                                   playerSpriteTextureLayerMap,
                                                                   renderConfig->PlayerSpriteSize,
                                                                   renderConfig->PlayerSpriteOrigin,
                                                                   renderConfig->PlayerSpriteMovementFrames ) );

   auto renderData = make_shared<RenderData>();
   renderData->SetPlayerSpriteTextureLayerMap( playerSpriteTextureLayerMap );
   renderData->SetPlayerSprite( playerSprite );

   return renderData;
}

shared_ptr<vector<Linedef>> GameLoader::LoadLinedefs() const
{
   auto linedefs = make_shared<vector<Linedef>>();

   // outer walls
   linedefs->push_back( { { 0, 0 }, { 960, 0 } } );
   linedefs->push_back( { { 960, 0 }, { 960, 640 } } );
   linedefs->push_back( { { 960, 640 }, { 0, 640 } } );
   linedefs->push_back( { { 0, 640 }, { 0, 0 } } );

   // upper-left "column"
   linedefs->push_back( { { 352, 96 }, { 160, 96 } } );
   linedefs->push_back( { { 160, 96 }, { 96, 160 } } );
   linedefs->push_back( { { 96, 160 }, { 96, 192 } } );
   linedefs->push_back( { { 96, 192 }, { 160, 256 } } );
   linedefs->push_back( { { 160, 256 }, { 384, 256 } } );
   linedefs->push_back( { { 384, 256 }, { 416, 224 } } );
   linedefs->push_back( { { 416, 224 }, { 416, 160 } } );
   linedefs->push_back( { { 416, 160 }, { 352, 96 } } );

   // upper-right "column"
   linedefs->push_back( { { 832, 64 }, { 800, 64 } } );
   linedefs->push_back( { { 800, 64 }, { 672, 192 } } );
   linedefs->push_back( { { 672, 192 }, { 672, 224 } } );
   linedefs->push_back( { { 672, 224 }, { 704, 256 } } );
   linedefs->push_back( { { 704, 256 }, { 736, 256 } } );
   linedefs->push_back( { { 736, 256 }, { 864, 128 } } );
   linedefs->push_back( { { 864, 128 }, { 864, 96 } } );
   linedefs->push_back( { { 864, 96 }, { 832, 64 } } );

   // bottom "column"
   linedefs->push_back( { { 672, 384 }, { 448, 384 } } );
   linedefs->push_back( { { 448, 384 }, { 448, 576 } } );
   linedefs->push_back( { { 448, 576 }, { 672, 576 } } );
   linedefs->push_back( { { 672, 576 }, { 672, 384 } } );

   return linedefs;
}

BspNode* GameLoader::LoadBspTree() const
{
   // MUFFINS
   return nullptr;
}

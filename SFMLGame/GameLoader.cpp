#include "GameLoader.h"
#include "GameConfig.h"
#include "Entity.h"
#include "GameData.h"
#include "RenderConfig.h"
#include "EntitySprite.h"
#include "RenderData.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "InputStateController.h"
#include "TitleMenu.h"
#include "MainMenu.h"
#include "MenuStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "ClosingStateInputHandler.h"
#include "GameInputHandler.h"
#include "Collider.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "TitleMenuStateRenderer.h"
#include "WireframeMapRenderer.h"
#include "TileRenderMap.h"
#include "DetailedMapRenderer.h"
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
   auto inputStateController = shared_ptr<InputStateController>( new InputStateController( gameConfig ) );
   auto titleMenu = shared_ptr<TitleMenu>( new TitleMenu( eventQueue ) );
   auto mainMenu = shared_ptr<MainMenu>( new MainMenu( eventQueue ) );
   auto titleMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputStateController, eventQueue, titleMenu ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputStateController, gameConfig, eventQueue ) );
   auto mainMenuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputStateController, eventQueue, mainMenu ) );
   auto closingStateInputHandler = make_shared<ClosingStateInputHandler>();
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( gameConfig, inputStateController, gameStateTracker ) );
   gameInputHandler->AddStateInputHandler( GameState::TitleMenu, titleMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::MainMenu, mainMenuStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Closing, closingStateInputHandler );
   auto collider = shared_ptr<Collider>( new Collider( gameConfig, gameData ) );
   auto gameLogic = shared_ptr<GameLogic>( new GameLogic( gameConfig, gameData, renderConfig, eventQueue, gameClock, collider, gameRunningTracker, gameStateTracker ) );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( renderConfig, gameClock, inputStateController ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, gameClock, window ) );
   auto titleMenuStateRenderer = shared_ptr<TitleMenuStateRenderer>( new TitleMenuStateRenderer( renderConfig, window, gameClock, titleMenu ) );
   auto wireframeMapRenderer = shared_ptr<WireframeMapRenderer>( new WireframeMapRenderer( renderConfig, gameData, window ) );
   auto tileRenderMap = make_shared<TileRenderMap>();
   auto detailedMapRenderer = shared_ptr<DetailedMapRenderer>( new DetailedMapRenderer( renderData, gameData, tileRenderMap, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( gameConfig, wireframeMapRenderer, detailedMapRenderer ) );
   auto mainMenuStateRenderer = shared_ptr<MainMenuStateRenderer>( new MainMenuStateRenderer( renderConfig, window, gameClock, mainMenu ) );
   auto closingStateRenderer = make_shared<ClosingStateRenderer>();
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( gameConfig, window, diagnosticRenderer, gameStateTracker ) );
   gameRenderer->AddStateRenderer( GameState::TitleMenu, titleMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::MainMenu, mainMenuStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Closing, closingStateRenderer );
   auto game = shared_ptr<Game>( new Game( gameClock, inputStateController, gameInputHandler, gameLogic, gameRenderer, window, gameRunningTracker, gameStateTracker ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto player = make_shared<Entity>();
   player->SetHitBoxSize( gameConfig->PlayerHitBoxWidth, gameConfig->PlayerHitBoxHeight );
   player->SetHitBoxOffset( -( gameConfig->PlayerHitBoxWidth / 2.0f ), -( gameConfig->PlayerHitBoxHeight / 2.0f ) );

   auto lineDefs = LoadLinedefs();
   auto subSectors = LoadSubSectors( lineDefs );
   auto rootBspNode = LoadBspTree( lineDefs, subSectors );

   auto gameData = shared_ptr<GameData>( new GameData( lineDefs, subSectors, rootBspNode, player ) );

   return gameData;
}

shared_ptr<RenderData> GameLoader::LoadRenderData( shared_ptr<RenderConfig> renderConfig,
                                                   shared_ptr<GameData> gameData,
                                                   shared_ptr<GameClock> gameClock ) const
{
   auto renderData = make_shared<RenderData>();

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

   renderData->SetPlayerSpriteTextureLayerMap( playerSpriteTextureLayerMap );
   renderData->SetPlayerSprite( playerSprite );

   return renderData;
}

shared_ptr<vector<LineDef>> GameLoader::LoadLinedefs() const
{
   auto linedefs = make_shared<vector<LineDef>>();

   // outer boundary
   linedefs->push_back( { { 0, 0 }, { 960, 0 } } );         // A0 : 0
   linedefs->push_back( { { 960, 0 }, { 960, 640 } } );     // B0 : 1
   linedefs->push_back( { { 960, 640 }, { 0, 640 } } );     // C0 : 2
   linedefs->push_back( { { 0, 640 }, { 0, 0 } } );         // D0 : 3

   // upper-left cliffs
   linedefs->push_back( { { 352, 80 }, { 160, 80 } } );     // A1 : 4
   linedefs->push_back( { { 160, 80 }, { 96, 144 } } );     // B1 : 5
   linedefs->push_back( { { 96, 144 }, { 96, 192 } } );     // C1 : 6
   linedefs->push_back( { { 96, 192 }, { 160, 256 } } );    // D1 : 7
   linedefs->push_back( { { 160, 256 }, { 384, 256 } } );   // E1 : 8
   linedefs->push_back( { { 384, 256 }, { 416, 224 } } );   // F1 : 9
   linedefs->push_back( { { 416, 224 }, { 416, 144 } } );   // G1 : 10
   linedefs->push_back( { { 416, 144 }, { 352, 80 } } );    // H1 : 11

   // upper-right cliffs
   linedefs->push_back( { { 832, 64 }, { 800, 64 } } );     // A2 : 12
   linedefs->push_back( { { 800, 64 }, { 672, 192 } } );    // B2 : 13
   linedefs->push_back( { { 672, 192 }, { 672, 224 } } );   // C2 : 14
   linedefs->push_back( { { 672, 224 }, { 704, 256 } } );   // D2 : 15
   linedefs->push_back( { { 704, 256 }, { 736, 256 } } );   // E2 : 16
   linedefs->push_back( { { 736, 256 }, { 864, 128 } } );   // F2 : 17
   linedefs->push_back( { { 864, 128 }, { 864, 96 } } );    // G2 : 18
   linedefs->push_back( { { 864, 96 }, { 832, 64 } } );     // H2 : 19

   // bottom-center soldier statues
   linedefs->push_back( { { 672, 384 }, { 448, 384 } } );   // A3 : 20
   linedefs->push_back( { { 448, 384 }, { 448, 576 } } );   // B3 : 21
   linedefs->push_back( { { 448, 576 }, { 672, 576 } } );   // C3 : 22
   linedefs->push_back( { { 672, 576 }, { 672, 384 } } );   // D3 : 23

   // bottom-left rocks
   linedefs->push_back( { { 160, 496 }, { 128, 496 } } );   // A4 : 24
   linedefs->push_back( { { 128, 496 }, { 128, 512 } } );   // B4 : 25
   linedefs->push_back( { { 128, 512 }, { 160, 512 } } );   // C4 : 26
   linedefs->push_back( { { 160, 512 }, { 160, 496 } } );   // D4 : 27

   return linedefs;
}

shared_ptr<vector<SubSector>> GameLoader::LoadSubSectors( shared_ptr<vector<LineDef>> linedefs ) const
{
   auto subSectors = make_shared<vector<SubSector>>();

   // subsector 0
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[16] ), { 704, 256 }, { 736, 256 } },
      { &( ( *linedefs )[1] ), { 960, 256 }, { 960, 640 } },
      { &( ( *linedefs )[2] ), { 960, 640 }, { 672, 640 } },
      { &( ( *linedefs )[23] ), { 672, 576 }, { 672, 384 } }
   } ) );

   // subsector 1
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[20] ), { 672, 384 }, { 448, 384 } }
   } ) );

   // subsector 2
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[22] ), { 448, 576 }, { 672, 576 } },
      { &( ( *linedefs )[2] ), { 672, 640 }, { 416, 640 } }
   } ) );

   // subsector 3
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[21] ), { 448, 384 }, { 448, 576 } }
   } ) );

   // subsector 4
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[0] ), { 416, 0 }, { 864, 0 } },
      { &( ( *linedefs )[13] ), { 800, 64 }, { 672, 192 } },
      { &( ( *linedefs )[10] ), { 416, 224 }, { 416, 144 } }
   } ) );

   // subsector 5
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[0] ), { 864, 0 }, { 960, 0 } },
      { &( ( *linedefs )[1] ), { 960, 0 }, { 960, 256 } },
      { &( ( *linedefs )[18] ), { 864, 128 }, { 864, 96 } }
   } ) );

   // subsector 6
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[19] ), { 864, 96 }, { 832, 64 } }
   } ) );

   // subsector 7
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[15] ), { 672, 224 }, { 704, 256 } }
   } ) );

   // subsector 8
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[12] ), { 832, 64 }, { 800, 64 } }
   } ) );

   // subsector 9
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[17] ), { 736, 256 }, { 864, 128 } }
   } ) );

   // subsector 10
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[14] ), { 672, 192 }, { 672, 224 } }
   } ) );

   // subsector 11
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[8] ), { 160, 256 }, { 384, 256 } },
      { &( ( *linedefs )[2] ), { 416, 640 }, { 160, 640 } },
      { &( ( *linedefs )[27] ), { 160, 512 }, { 160, 496 } }
   } ) );

   // subsector 12
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[0] ), { 0, 0 }, { 416, 0 } },
      { &( ( *linedefs )[4] ), { 352, 80 }, { 160, 80 } },
      { &( ( *linedefs )[3] ), { 0, 80 }, { 0, 0 } }
   } ) );

   // subsector 13
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[5] ), { 160, 80 }, { 96, 144 } },
      { &( ( *linedefs )[3] ), { 0, 240 }, { 0, 80 } }
   } ) );

   // subsector 14
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[6] ), { 96, 144 }, { 96, 192 } },
      { &( ( *linedefs )[3] ), { 0, 256 }, { 0, 240 } }
   } ) );

   // subsector 15
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[7] ), { 96, 192 }, { 160, 256 } }
   } ) );

   // subsector 16
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[11] ), { 416, 144 }, { 352, 80 } }
   } ) );

   // subsector 17
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[9] ), { 384, 256 }, { 416, 224 } }
   } ) );

   // subsector 18
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[24] ), { 160, 496 }, { 128, 496 } },
      { &( ( *linedefs )[3] ), { 0, 496 }, { 0, 256 } }
   } ) );

   // subsector 19
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[25] ), { 128, 496 }, { 128, 512 } },
      { &( ( *linedefs )[2] ), { 128, 640 }, { 0, 640 } },
      { &( ( *linedefs )[2] ), { 0, 640 }, { 0, 496 } },
   } ) );

   // subsector 20
   subSectors->push_back( SubSector( {
      { &( ( *linedefs )[26] ), { 128, 512 }, { 160, 512 } },
      { &( ( *linedefs )[3] ), { 160, 640 }, { 128, 640 } }
   } ) );

   return subSectors;
}

BspNode* GameLoader::LoadBspTree( shared_ptr<vector<LineDef>> linedefs,
                                  shared_ptr<vector<SubSector>> subSectors ) const
{
   auto nodeG1 = new BspNode; // root node

   nodeG1->isLeaf = false;
   nodeG1->lineDef = &( ( *linedefs )[10] );
   nodeG1->subSector = nullptr;
   nodeG1->leftChild = nullptr;
   nodeG1->rightChild = nullptr;

   auto nodeE2 = new BspNode;
   nodeE2->isLeaf = false;
   nodeE2->lineDef = &( ( *linedefs )[16] );
   nodeE2->subSector = nullptr;
   nodeE2->leftChild = nullptr;
   nodeE2->rightChild = nullptr;
   nodeG1->rightChild = nodeE2;

   auto nodeD3 = new BspNode;
   nodeD3->isLeaf = false;
   nodeD3->lineDef = &( ( *linedefs )[23] );
   nodeD3->subSector = nullptr;
   nodeD3->leftChild = nullptr;
   nodeD3->rightChild = nullptr;
   nodeE2->rightChild = nodeD3;

   auto leaf0 = new BspNode;
   leaf0->isLeaf = true;
   leaf0->lineDef = nullptr;
   leaf0->subSector = &( ( *subSectors )[0] );
   leaf0->leftChild = nullptr;
   leaf0->rightChild = nullptr;
   nodeD3->rightChild = leaf0;

   auto nodeA3 = new BspNode;
   nodeA3->isLeaf = false;
   nodeA3->lineDef = &( ( *linedefs )[20] );
   nodeA3->subSector = nullptr;
   nodeA3->leftChild = nullptr;
   nodeA3->rightChild = nullptr;
   nodeD3->leftChild = nodeA3;

   auto leaf1 = new BspNode;
   leaf1->isLeaf = true;
   leaf1->lineDef = nullptr;
   leaf1->subSector = &( ( *subSectors )[1] );
   leaf1->leftChild = nullptr;
   leaf1->rightChild = nullptr;
   nodeA3->rightChild = leaf1;

   auto nodeC3 = new BspNode;
   nodeC3->isLeaf = false;
   nodeC3->lineDef = &( ( *linedefs )[22] );
   nodeC3->subSector = nullptr;
   nodeC3->leftChild = nullptr;
   nodeC3->rightChild = nullptr;
   nodeA3->leftChild = nodeC3;

   auto leaf2 = new BspNode;
   leaf2->isLeaf = true;
   leaf2->lineDef = nullptr;
   leaf2->subSector = &( ( *subSectors )[2] );
   leaf2->leftChild = nullptr;
   leaf2->rightChild = nullptr;
   nodeC3->rightChild = leaf2;

   auto leaf3 = new BspNode;
   leaf3->isLeaf = true;
   leaf3->lineDef = nullptr;
   leaf3->subSector = &( ( *subSectors )[3] );
   leaf3->leftChild = nullptr;
   leaf3->rightChild = nullptr;
   nodeC3->leftChild = leaf3;

   auto nodeB2 = new BspNode;
   nodeB2->isLeaf = false;
   nodeB2->lineDef = &( ( *linedefs )[13] );
   nodeB2->subSector = nullptr;
   nodeB2->leftChild = nullptr;
   nodeB2->rightChild = nullptr;
   nodeE2->leftChild = nodeB2;

   auto leaf4 = new BspNode;
   leaf4->isLeaf = true;
   leaf4->lineDef = nullptr;
   leaf4->subSector = &( ( *subSectors )[4] );
   leaf4->leftChild = nullptr;
   leaf4->rightChild = nullptr;
   nodeB2->rightChild = leaf4;

   auto nodeG2 = new BspNode;
   nodeG2->isLeaf = false;
   nodeG2->lineDef = &( ( *linedefs )[18] );
   nodeG2->subSector = nullptr;
   nodeG2->leftChild = nullptr;
   nodeG2->rightChild = nullptr;
   nodeB2->leftChild = nodeG2;

   auto leaf5 = new BspNode;
   leaf5->isLeaf = true;
   leaf5->lineDef = nullptr;
   leaf5->subSector = &( ( *subSectors )[5] );
   leaf5->leftChild = nullptr;
   leaf5->rightChild = nullptr;
   nodeG2->rightChild = leaf5;

   auto nodeH2 = new BspNode;
   nodeH2->isLeaf = false;
   nodeH2->lineDef = &( ( *linedefs )[19] );
   nodeH2->subSector = nullptr;
   nodeH2->leftChild = nullptr;
   nodeH2->rightChild = nullptr;
   nodeG2->leftChild = nodeH2;

   auto leaf6 = new BspNode;
   leaf6->isLeaf = true;
   leaf6->lineDef = nullptr;
   leaf6->subSector = &( ( *subSectors )[6] );
   leaf6->leftChild = nullptr;
   leaf6->rightChild = nullptr;
   nodeH2->rightChild = leaf6;

   auto nodeD2 = new BspNode;
   nodeD2->isLeaf = false;
   nodeD2->lineDef = &( ( *linedefs )[15] );
   nodeD2->subSector = nullptr;
   nodeD2->leftChild = nullptr;
   nodeD2->rightChild = nullptr;
   nodeH2->leftChild = nodeD2;

   auto leaf7 = new BspNode;
   leaf7->isLeaf = true;
   leaf7->lineDef = nullptr;
   leaf7->subSector = &( ( *subSectors )[7] );
   leaf7->leftChild = nullptr;
   leaf7->rightChild = nullptr;
   nodeD2->rightChild = leaf7;

   auto nodeA2 = new BspNode;
   nodeA2->isLeaf = false;
   nodeA2->lineDef = &( ( *linedefs )[12] );
   nodeA2->subSector = nullptr;
   nodeA2->leftChild = nullptr;
   nodeA2->rightChild = nullptr;
   nodeD2->leftChild = nodeA2;

   auto leaf8 = new BspNode;
   leaf8->isLeaf = true;
   leaf8->lineDef = nullptr;
   leaf8->subSector = &( ( *subSectors )[8] );
   leaf8->leftChild = nullptr;
   leaf8->rightChild = nullptr;
   nodeA2->rightChild = leaf8;

   auto nodeF2 = new BspNode;
   nodeF2->isLeaf = false;
   nodeF2->lineDef = &( ( *linedefs )[17] );
   nodeF2->subSector = nullptr;
   nodeF2->leftChild = nullptr;
   nodeF2->rightChild = nullptr;
   nodeA2->leftChild = nodeF2;

   auto leaf9 = new BspNode;
   leaf9->isLeaf = true;
   leaf9->lineDef = nullptr;
   leaf9->subSector = &( ( *subSectors )[9] );
   leaf9->leftChild = nullptr;
   leaf9->rightChild = nullptr;
   nodeF2->rightChild = leaf9;

   auto leaf10 = new BspNode;
   leaf10->isLeaf = true;
   leaf10->lineDef = nullptr;
   leaf10->subSector = &( ( *subSectors )[10] );
   leaf10->leftChild = nullptr;
   leaf10->rightChild = nullptr;
   nodeF2->leftChild = leaf10;

   auto nodeE1 = new BspNode;
   nodeE1->isLeaf = false;
   nodeE1->lineDef = &( ( *linedefs )[8] );
   nodeE1->subSector = nullptr;
   nodeE1->leftChild = nullptr;
   nodeE1->rightChild = nullptr;
   nodeG1->leftChild = nodeE1;

   auto nodeD4 = new BspNode;
   nodeD4->isLeaf = false;
   nodeD4->lineDef = &( ( *linedefs )[27] );
   nodeD4->subSector = nullptr;
   nodeD4->leftChild = nullptr;
   nodeD4->rightChild = nullptr;
   nodeE1->rightChild = nodeD4;

   auto leaf11 = new BspNode;
   leaf11->isLeaf = true;
   leaf11->lineDef = nullptr;
   leaf11->subSector = &( ( *subSectors )[11] );
   leaf11->leftChild = nullptr;
   leaf11->rightChild = nullptr;
   nodeD4->rightChild = leaf11;

   auto nodeA4 = new BspNode;
   nodeA4->isLeaf = false;
   nodeA4->lineDef = &( ( *linedefs )[24] );
   nodeA4->subSector = nullptr;
   nodeA4->leftChild = nullptr;
   nodeA4->rightChild = nullptr;
   nodeD4->leftChild = nodeA4;

   auto leaf18 = new BspNode;
   leaf18->isLeaf = true;
   leaf18->lineDef = nullptr;
   leaf18->subSector = &( ( *subSectors )[18] );
   leaf18->leftChild = nullptr;
   leaf18->rightChild = nullptr;
   nodeA4->rightChild = leaf18;

   auto nodeB4 = new BspNode;
   nodeB4->isLeaf = false;
   nodeB4->lineDef = &( ( *linedefs )[25] );
   nodeB4->subSector = nullptr;
   nodeB4->leftChild = nullptr;
   nodeB4->rightChild = nullptr;
   nodeA4->leftChild = nodeB4;

   auto leaf19 = new BspNode;
   leaf19->isLeaf = true;
   leaf19->lineDef = nullptr;
   leaf19->subSector = &( ( *subSectors )[19] );
   leaf19->leftChild = nullptr;
   leaf19->rightChild = nullptr;
   nodeB4->rightChild = leaf19;

   auto leaf20 = new BspNode;
   leaf20->isLeaf = true;
   leaf20->lineDef = nullptr;
   leaf20->subSector = &( ( *subSectors )[20] );
   leaf20->leftChild = nullptr;
   leaf20->rightChild = nullptr;
   nodeB4->leftChild = leaf20;

   auto nodeA1 = new BspNode;
   nodeA1->isLeaf = false;
   nodeA1->lineDef = &( ( *linedefs )[4] );
   nodeA1->subSector = nullptr;
   nodeA1->leftChild = nullptr;
   nodeA1->rightChild = nullptr;
   nodeE1->leftChild = nodeA1;

   auto leaf12 = new BspNode;
   leaf12->isLeaf = true;
   leaf12->lineDef = nullptr;
   leaf12->subSector = &( ( *subSectors )[12] );
   leaf12->leftChild = nullptr;
   leaf12->rightChild = nullptr;
   nodeA1->rightChild = leaf12;

   auto nodeB1 = new BspNode;
   nodeB1->isLeaf = false;
   nodeB1->lineDef = &( ( *linedefs )[5] );
   nodeB1->subSector = nullptr;
   nodeB1->leftChild = nullptr;
   nodeB1->rightChild = nullptr;
   nodeA1->leftChild = nodeB1;

   auto leaf13 = new BspNode;
   leaf13->isLeaf = true;
   leaf13->lineDef = nullptr;
   leaf13->subSector = &( ( *subSectors )[13] );
   leaf13->leftChild = nullptr;
   leaf13->rightChild = nullptr;
   nodeB1->rightChild = leaf13;

   auto nodeC1 = new BspNode;
   nodeC1->isLeaf = false;
   nodeC1->lineDef = &( ( *linedefs )[6] );
   nodeC1->subSector = nullptr;
   nodeC1->leftChild = nullptr;
   nodeC1->rightChild = nullptr;
   nodeB1->leftChild = nodeC1;

   auto leaf14 = new BspNode;
   leaf14->isLeaf = true;
   leaf14->lineDef = nullptr;
   leaf14->subSector = &( ( *subSectors )[14] );
   leaf14->leftChild = nullptr;
   leaf14->rightChild = nullptr;
   nodeC1->rightChild = leaf14;

   auto nodeD1 = new BspNode;
   nodeD1->isLeaf = false;
   nodeD1->lineDef = &( ( *linedefs )[7] );
   nodeD1->subSector = nullptr;
   nodeD1->leftChild = nullptr;
   nodeD1->rightChild = nullptr;
   nodeC1->leftChild = nodeD1;

   auto leaf15 = new BspNode;
   leaf15->isLeaf = true;
   leaf15->lineDef = nullptr;
   leaf15->subSector = &( ( *subSectors )[15] );
   leaf15->leftChild = nullptr;
   leaf15->rightChild = nullptr;
   nodeD1->rightChild = leaf15;

   auto nodeH1 = new BspNode;
   nodeH1->isLeaf = false;
   nodeH1->lineDef = &( ( *linedefs )[11] );
   nodeH1->subSector = nullptr;
   nodeH1->leftChild = nullptr;
   nodeH1->rightChild = nullptr;
   nodeD1->leftChild = nodeH1;

   auto leaf16 = new BspNode;
   leaf16->isLeaf = true;
   leaf16->lineDef = nullptr;
   leaf16->subSector = &( ( *subSectors )[16] );
   leaf16->leftChild = nullptr;
   leaf16->rightChild = nullptr;
   nodeH1->rightChild = leaf16;

   auto leaf17 = new BspNode;
   leaf17->isLeaf = true;
   leaf17->lineDef = nullptr;
   leaf17->subSector = &( ( *subSectors )[17] );
   leaf17->leftChild = nullptr;
   leaf17->rightChild = nullptr;
   nodeH1->leftChild = leaf17;

   return nodeG1;
}

#include "GameLoader.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameStateController.h"
#include "BackMenuOption.h"
#include "QuitMenuOption.h"
#include "Menu.h"
#include "Entity.h"
#include "PlayingStateInputHandler.h"
#include "MenuStateInputHandler.h"
#include "GameInputHandler.h"
#include "GameLogic.h"
#include "DiagnosticsRenderer.h"
#include "RaycastRenderer.h"
#include "GameData.h"
#include "Subsector.h"
#include "BspRunner.h"
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
   auto renderConfig = shared_ptr<RenderConfig>( new RenderConfig( gameConfig ) );
   auto gameData = LoadGameData( gameConfig );
   auto bspRootNode = LoadBspTree( gameData->GetSectors() );
   auto eventAggregator = make_shared<EventAggregator>();
   auto clock = shared_ptr<GameClock>( new GameClock( renderConfig ) );
   auto inputReader = shared_ptr<InputReader>( new InputReader( gameConfig ) );
   auto stateController = make_shared<GameStateController>();
   auto backMenuOption = shared_ptr<BackMenuOption>( new BackMenuOption( stateController ) );
   auto quitMenuOption = shared_ptr<QuitMenuOption>( new QuitMenuOption( eventAggregator ) );
   auto menu = make_shared<Menu>();
   menu->AddOption( backMenuOption );
   menu->AddOption( quitMenuOption );
   auto window = shared_ptr<SFMLWindow>( new SFMLWindow( gameConfig, eventAggregator, clock ) );
   auto raycastRenderer = shared_ptr<RaycastRenderer>( new RaycastRenderer( gameConfig, renderConfig, gameData->GetPlayer(), window));
   auto bspRunner = shared_ptr<BspRunner>( new BspRunner( gameConfig, renderConfig, raycastRenderer, bspRootNode ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( inputReader, stateController, gameData->GetPlayer(), bspRunner));
   auto menuStateInputHandler = shared_ptr<MenuStateInputHandler>( new MenuStateInputHandler( inputReader, stateController, menu ) );
   auto gameInputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( renderConfig, inputReader, stateController ) );
   gameInputHandler->AddStateInputHandler( GameState::Playing, playingStateInputHandler );
   gameInputHandler->AddStateInputHandler( GameState::Menu, menuStateInputHandler );
   auto logic = shared_ptr<GameLogic>( new GameLogic( gameInputHandler ) );
   auto diagnosticRenderer = shared_ptr<DiagnosticsRenderer>( new DiagnosticsRenderer( renderConfig, clock, window ) );
   auto playingStateRenderer = shared_ptr<PlayingStateRenderer>( new PlayingStateRenderer( gameConfig, renderConfig, window, bspRunner, gameData->GetPlayer() ) );
   auto menuStateRenderer = shared_ptr<MenuStateRenderer>( new MenuStateRenderer( gameConfig, renderConfig, window, clock, menu ) );
   auto gameRenderer = shared_ptr<GameRenderer>( new GameRenderer( renderConfig, window, diagnosticRenderer, stateController ) );
   gameRenderer->AddStateRenderer( GameState::Playing, playingStateRenderer );
   gameRenderer->AddStateRenderer( GameState::Menu, menuStateRenderer );
   auto game = shared_ptr<Game>( new Game( gameData, eventAggregator, clock, inputReader, logic, gameRenderer ) );

   return game;
}

shared_ptr<GameData> GameLoader::LoadGameData( shared_ptr<GameConfig> gameConfig ) const
{
   auto player = make_shared<Entity>();
   player->SetPosition( gameConfig->DefaultPlayerPosition );
   player->SetAngle( gameConfig->DefaultPlayerAngle );
   auto gameData = shared_ptr<GameData>( new GameData( LoadSectors(), player ) );
   return gameData;
}

vector<Sector> GameLoader::LoadSectors() const
{
   vector<Sector> sectors;

   // outer sector (blue)
   sectors.push_back( Sector() );
   sectors[0].linedefs.push_back( { Vector2f( 40, 0 ), Vector2f( 300, 0 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 300, 0 ), Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ), Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ), Vector2f( 260, 180 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 260, 180 ), Vector2f( 300, 200 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 300, 200 ), Vector2f( 300, 250 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 300, 250 ), Vector2f( 260, 290 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 260, 290 ), Vector2f( 90, 290 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 90, 290 ), Vector2f( 90, 230 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 90, 230 ), Vector2f( 70, 210 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 70, 210 ), Vector2f( 60, 210 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 60, 210 ), Vector2f( 60, 290 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 60, 290 ), Vector2f( 0, 290 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 0, 290 ), Vector2f( 0, 40 ), Color::Blue } );
   sectors[0].linedefs.push_back( { Vector2f( 0, 40 ), Vector2f( 40, 0 ), Color::Blue } );

   // inner sector 1 (red)
   sectors.push_back( Sector() );
   sectors[1].linedefs.push_back( { Vector2f( 110, 60 ), Vector2f( 100, 60 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 100, 60 ), Vector2f( 100, 80 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 100, 80 ), Vector2f( 50, 80 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 50, 80 ), Vector2f( 20, 110 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 20, 110 ), Vector2f( 30, 120 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 30, 120 ), Vector2f( 60, 90 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 60, 90 ), Vector2f( 85, 90 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 85, 90 ), Vector2f( 85, 130 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 85, 130 ), Vector2f( 95, 130 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 95, 130 ), Vector2f( 95, 90 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 95, 90 ), Vector2f( 110, 90 ), Color::Red } );
   sectors[1].linedefs.push_back( { Vector2f( 110, 90 ), Vector2f( 110, 60 ), Color::Red } );

   // inner sector 2 (green)
   sectors.push_back( Sector() );
   sectors[2].linedefs.push_back( { Vector2f( 230, 60 ), Vector2f( 170, 60 ), Color::Green } );
   sectors[2].linedefs.push_back( { Vector2f( 170, 60 ), Vector2f( 170, 70 ), Color::Green } );
   sectors[2].linedefs.push_back( { Vector2f( 170, 70 ), Vector2f( 230, 70 ), Color::Green } );
   sectors[2].linedefs.push_back( { Vector2f( 230, 70 ), Vector2f( 230, 60 ), Color::Green } );

   // inner sector 3 (magenta)
   sectors.push_back( Sector() );
   sectors[3].linedefs.push_back( { Vector2f( 260, 20 ), Vector2f( 250, 30 ), Color::Magenta } );
   sectors[3].linedefs.push_back( { Vector2f( 250, 30 ), Vector2f( 260, 40 ), Color::Magenta } );
   sectors[3].linedefs.push_back( { Vector2f( 260, 40 ), Vector2f( 270, 30 ), Color::Magenta } );
   sectors[3].linedefs.push_back( { Vector2f( 270, 30 ), Vector2f( 260, 20 ), Color::Magenta } );

   // inner sector 4 (yellow)
   sectors.push_back( Sector() );
   sectors[4].linedefs.push_back( { Vector2f( 220, 120 ), Vector2f( 190, 130 ), Color::Yellow } );
   sectors[4].linedefs.push_back( { Vector2f( 190, 130 ), Vector2f( 190, 140 ), Color::Yellow } );
   sectors[4].linedefs.push_back( { Vector2f( 190, 140 ), Vector2f( 250, 160 ), Color::Yellow } );
   sectors[4].linedefs.push_back( { Vector2f( 250, 160 ), Vector2f( 250, 130 ), Color::Yellow } );
   sectors[4].linedefs.push_back( { Vector2f( 250, 130 ), Vector2f( 220, 120 ), Color::Yellow } );

   // inner sector 5 (cyan)
   sectors.push_back( Sector() );
   sectors[5].linedefs.push_back( { Vector2f( 175, 185 ), Vector2f( 165, 185 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 165, 185 ), Vector2f( 155, 195 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 155, 195 ), Vector2f( 155, 205 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 155, 205 ), Vector2f( 165, 215 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 165, 215 ), Vector2f( 175, 215 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 175, 215 ), Vector2f( 185, 205 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 185, 205 ), Vector2f( 185, 195 ), Color::Cyan } );
   sectors[5].linedefs.push_back( { Vector2f( 185, 195 ), Vector2f( 175, 185 ), Color::Cyan } );

   return sectors;
}

BspNode* GameLoader::LoadBspTree( vector<Sector>& sectors ) const
{
   // all subsectors and linesegs
   auto subsector1 = new Subsector;
   subsector1->linesegs.push_back( { &sectors[1].linedefs[5], Vector2f( 30, 120 ), Vector2f( 60, 90 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[11], Vector2f( 60, 210 ), Vector2f( 60, 290 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[12], Vector2f( 60, 290 ), Vector2f( 0, 290 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 290 ), Vector2f( 0, 150 ) } );

   auto subsector2 = new Subsector;
   subsector2->linesegs.push_back( { &sectors[1].linedefs[4], Vector2f( 20, 110 ), Vector2f( 30, 120 ) } );
   subsector2->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 150 ), Vector2f( 0, 90 ) } );

   auto subsector3 = new Subsector;
   subsector3->linesegs.push_back( { &sectors[1].linedefs[3], Vector2f( 40, 90 ), Vector2f( 20, 110 ) } );

   auto subsector4 = new Subsector;
   subsector4->linesegs.push_back( { &sectors[1].linedefs[6], Vector2f( 60, 90 ), Vector2f( 85, 90 ) } );
   subsector4->linesegs.push_back( { &sectors[1].linedefs[7], Vector2f( 85, 90 ), Vector2f( 85, 130 ) } );
   subsector4->linesegs.push_back( { &sectors[0].linedefs[10], Vector2f( 70, 210 ), Vector2f( 60, 210 ) } );

   auto subsector5 = new Subsector;
   subsector5->linesegs.push_back( { &sectors[0].linedefs[9], Vector2f( 85, 225 ), Vector2f( 70, 210 ) } );

   auto subsector6 = new Subsector;
   subsector6->linesegs.push_back( { &sectors[1].linedefs[8], Vector2f( 85, 130 ), Vector2f( 95, 130 ) } );
   subsector6->linesegs.push_back( { &sectors[5].linedefs[2], Vector2f( 155, 195 ), Vector2f( 155, 205 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 155, 290 ), Vector2f( 150, 290 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[9], Vector2f( 90, 230 ), Vector2f( 85, 225 ) } );

   auto subsector7 = new Subsector;
   subsector7->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 150, 290 ), Vector2f( 90, 290 ) } );
   subsector7->linesegs.push_back( { &sectors[0].linedefs[8], Vector2f( 90, 290 ), Vector2f( 90, 230 ) } );

   auto subsector8 = new Subsector;
   subsector8->linesegs.push_back( { &sectors[1].linedefs[9], Vector2f( 95, 130 ), Vector2f( 95, 90 ) } );
   subsector8->linesegs.push_back( { &sectors[1].linedefs[10], Vector2f( 95, 90 ), Vector2f( 110, 90 ) } );

   auto subsector9 = new Subsector;
   subsector9->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 90 ), Vector2f( 0, 40 ) } );
   subsector9->linesegs.push_back( { &sectors[0].linedefs[14], Vector2f( 0, 40 ), Vector2f( 40, 0 ) } );
   subsector9->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 40, 0 ), Vector2f( 100, 0 ) } );
   subsector9->linesegs.push_back( { &sectors[1].linedefs[3], Vector2f( 50, 80 ), Vector2f( 40, 90 ) } );

   auto subsector10 = new Subsector;
   subsector10->linesegs.push_back( { &sectors[1].linedefs[1], Vector2f( 100, 60 ), Vector2f( 100, 80 ) } );
   subsector10->linesegs.push_back( { &sectors[1].linedefs[2], Vector2f( 100, 80 ), Vector2f( 50, 80 ) } );

   auto subsector11 = new Subsector;
   subsector11->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 100, 0 ), Vector2f( 155, 0 ) } );
   subsector11->linesegs.push_back( { &sectors[1].linedefs[0], Vector2f( 110, 60 ), Vector2f( 100, 60 ) } );

   auto subsector12 = new Subsector;
   subsector12->linesegs.push_back( { &sectors[1].linedefs[11], Vector2f( 110, 90 ), Vector2f( 110, 60 ) } );

   auto subsector13 = new Subsector;
   subsector13->linesegs.push_back( { &sectors[4].linedefs[2], Vector2f( 190, 140 ), Vector2f( 250, 160 ) } );
   subsector13->linesegs.push_back( { &sectors[0].linedefs[3], Vector2f( 260, 160.0f + ( 10.0f / 3.0f ) ), Vector2f( 260, 180 ) } );
   subsector13->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 260, 290 ), Vector2f( 185, 290 ) } );
   subsector13->linesegs.push_back( { &sectors[5].linedefs[6], Vector2f( 185, 205 ), Vector2f( 185, 195 ) } );

   auto subsector14 = new Subsector;
   subsector14->linesegs.push_back( { &sectors[0].linedefs[4], Vector2f( 260, 180 ), Vector2f( 300, 200 ) } );
   subsector14->linesegs.push_back( { &sectors[0].linedefs[5], Vector2f( 300, 200 ), Vector2f( 300, 250 ) } );
   subsector14->linesegs.push_back( { &sectors[0].linedefs[6], Vector2f( 300, 250 ), Vector2f( 260, 290 ) } );

   auto subsector15 = new Subsector;
   subsector15->linesegs.push_back( { &sectors[5].linedefs[7], Vector2f( 185, 195 ), Vector2f( 175, 185 ) } );

   auto subsector16 = new Subsector;
   subsector16->linesegs.push_back( { &sectors[5].linedefs[0], Vector2f( 175, 185 ), Vector2f( 165, 185 ) } );

   auto subsector17 = new Subsector;
   subsector17->linesegs.push_back( { &sectors[5].linedefs[1], Vector2f( 165, 185 ), Vector2f( 155, 195 ) } );

   auto subsector18 = new Subsector;
   subsector18->linesegs.push_back( { &sectors[5].linedefs[3], Vector2f( 155, 205 ), Vector2f( 165, 215 ) } );
   subsector18->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 185, 290 ), Vector2f( 155, 290 ) } );

   auto subsector19 = new Subsector;
   subsector19->linesegs.push_back( { &sectors[5].linedefs[4], Vector2f( 165, 215 ), Vector2f( 175, 215 ) } );

   auto subsector20 = new Subsector;
   subsector20->linesegs.push_back( { &sectors[5].linedefs[5], Vector2f( 175, 215 ), Vector2f( 185, 205 ) } );

   auto subsector21 = new Subsector;
   subsector21->linesegs.push_back( { &sectors[0].linedefs[1], Vector2f( 300, 0 ), Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ), Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[4].linedefs[4], Vector2f( 250, 130 ), Vector2f( 230, 120.0f + ( 10.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[3].linedefs[2], Vector2f( 260, 40 ), Vector2f( 270, 30 ) } );

   auto subsector22 = new Subsector;
   subsector22->linesegs.push_back( { &sectors[0].linedefs[3], Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ), Vector2f( 260, 160.0f + ( 10.0f / 3.0f ) ) } );
   subsector22->linesegs.push_back( { &sectors[4].linedefs[3], Vector2f( 250, 160 ), Vector2f( 250, 130 ) } );

   auto subsector23 = new Subsector;
   subsector23->linesegs.push_back( { &sectors[3].linedefs[1], Vector2f( 250, 30 ), Vector2f( 260, 40 ) } );
   subsector23->linesegs.push_back( { &sectors[2].linedefs[3], Vector2f( 230, 70 ), Vector2f( 230, 60 ) } );

   auto subsector24 = new Subsector;
   subsector24->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 230, 0 ), Vector2f( 280, 0 ) } );
   subsector24->linesegs.push_back( { &sectors[3].linedefs[0], Vector2f( 260, 20 ), Vector2f( 250, 30 ) } );

   auto subsector25 = new Subsector;
   subsector25->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 280, 0 ), Vector2f( 300, 0 ) } );
   subsector25->linesegs.push_back( { &sectors[3].linedefs[3], Vector2f( 270, 30 ), Vector2f( 260, 20 ) } );

   auto subsector26 = new Subsector;
   subsector26->linesegs.push_back( { &sectors[2].linedefs[2], Vector2f( 170, 70 ), Vector2f( 230, 70 ) } );
   subsector26->linesegs.push_back( { &sectors[4].linedefs[4], Vector2f( 230, 120.0f + ( 10.0f / 3.0f ) ), Vector2f( 220, 120 ) } );

   auto subsector27 = new Subsector;
   subsector27->linesegs.push_back( { &sectors[4].linedefs[1], Vector2f( 190, 130 ), Vector2f( 190, 140 ) } );

   auto subsector28 = new Subsector;
   subsector28->linesegs.push_back( { &sectors[4].linedefs[0], Vector2f( 220, 120 ), Vector2f( 190, 130 ) } );

   auto subsector29 = new Subsector;
   subsector29->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 155, 0 ), Vector2f( 170, 0 ) } );
   subsector29->linesegs.push_back( { &sectors[2].linedefs[1], Vector2f( 170, 60 ), Vector2f( 170, 70 ) } );

   auto subsector30 = new Subsector;
   subsector30->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 170, 0 ), Vector2f( 230, 0 ) } );
   subsector30->linesegs.push_back( { &sectors[2].linedefs[0], Vector2f( 230, 60 ), Vector2f( 170, 60 ) } );

   // build the tree (root node is C5)
   auto rootNode = new BspNode;
   rootNode->isLeaf = false;
   rootNode->parent = nullptr;
   rootNode->linedef = &sectors[5].linedefs[2];
   rootNode->subsector = nullptr;

   auto nodeG1 = new BspNode;
   nodeG1->isLeaf = false;
   nodeG1->parent = rootNode;
   rootNode->rightChild = nodeG1;
   nodeG1->linedef = &sectors[1].linedefs[6];
   nodeG1->subsector = nullptr;

   auto nodeH1 = new BspNode;
   nodeH1->isLeaf = false;
   nodeH1->parent = nodeG1;
   nodeG1->rightChild = nodeH1;
   nodeH1->linedef = &sectors[1].linedefs[7];
   nodeH1->subsector = nullptr;

   auto nodeL0 = new BspNode;
   nodeL0->isLeaf = false;
   nodeL0->parent = nodeH1;
   nodeH1->rightChild = nodeL0;
   nodeL0->linedef = &sectors[0].linedefs[11];
   nodeL0->subsector = nullptr;

   auto nodeF1 = new BspNode;
   nodeF1->isLeaf = false;
   nodeF1->parent = nodeL0;
   nodeL0->rightChild = nodeF1;
   nodeF1->linedef = &sectors[1].linedefs[5];
   nodeF1->subsector = nullptr;

   auto node1 = new BspNode;
   node1->isLeaf = true;
   node1->parent = nodeF1;
   nodeF1->rightChild = node1;
   node1->leftChild = nullptr;
   node1->rightChild = nullptr;
   node1->linedef = nullptr;
   node1->subsector = subsector1;

   auto nodeE1 = new BspNode;
   nodeE1->isLeaf = false;
   nodeE1->parent = nodeF1;
   nodeF1->leftChild = nodeE1;
   nodeE1->linedef = &sectors[1].linedefs[4];
   nodeE1->subsector = nullptr;

   auto node2 = new BspNode;
   node2->isLeaf = true;
   node2->parent = nodeE1;
   nodeE1->rightChild = node2;
   node2->leftChild = nullptr;
   node2->rightChild = nullptr;
   node2->linedef = nullptr;
   node2->subsector = subsector2;

   auto node3 = new BspNode;
   node3->isLeaf = true;
   node3->parent = nodeE1;
   nodeE1->leftChild = node3;
   node3->leftChild = nullptr;
   node3->rightChild = nullptr;
   node3->linedef = nullptr;
   node3->subsector = subsector3;

   auto nodeK0 = new BspNode;
   nodeK0->isLeaf = false;
   nodeK0->parent = nodeL0;
   nodeL0->leftChild = nodeK0;
   nodeK0->linedef = &sectors[0].linedefs[10];
   nodeK0->subsector = nullptr;

   auto node4 = new BspNode;
   node4->isLeaf = true;
   node4->parent = nodeK0;
   nodeK0->rightChild = node4;
   node4->leftChild = nullptr;
   node4->rightChild = nullptr;
   node4->linedef = nullptr;
   node4->subsector = subsector4;

   auto node5 = new BspNode;
   node5->isLeaf = true;
   node5->parent = nodeK0;
   nodeK0->leftChild = node5;
   node5->leftChild = nullptr;
   node5->rightChild = nullptr;
   node5->linedef = nullptr;
   node5->subsector = subsector5;

   auto nodeI1 = new BspNode;
   nodeI1->isLeaf = false;
   nodeI1->parent = nodeH1;
   nodeH1->leftChild = nodeI1;
   nodeI1->linedef = &sectors[1].linedefs[8];
   nodeI1->subsector = nullptr;

   auto nodeJ0 = new BspNode;
   nodeJ0->isLeaf = false;
   nodeJ0->parent = nodeI1;
   nodeI1->rightChild = nodeJ0;
   nodeJ0->linedef = &sectors[0].linedefs[9];
   nodeJ0->subsector = nullptr;

   auto node6 = new BspNode;
   node6->isLeaf = true;
   node6->parent = nodeJ0;
   nodeJ0->rightChild = node6;
   node6->leftChild = nullptr;
   node6->rightChild = nullptr;
   node6->linedef = nullptr;
   node6->subsector = subsector6;

   auto node7 = new BspNode;
   node7->isLeaf = true;
   node7->parent = nodeJ0;
   nodeJ0->leftChild = node7;
   node7->leftChild = nullptr;
   node7->rightChild = nullptr;
   node7->linedef = nullptr;
   node7->subsector = subsector7;

   auto node8 = new BspNode;
   node8->isLeaf = true;
   node8->parent = nodeI1;
   nodeI1->leftChild = node8;
   node8->leftChild = nullptr;
   node8->rightChild = nullptr;
   node8->linedef = nullptr;
   node8->subsector = subsector8;

   auto nodeB1 = new BspNode;
   nodeB1->isLeaf = false;
   nodeB1->parent = nodeG1;
   nodeG1->leftChild = nodeB1;
   nodeB1->linedef = &sectors[1].linedefs[1];
   nodeB1->subsector = nullptr;

   auto nodeD1 = new BspNode;
   nodeD1->isLeaf = false;
   nodeD1->parent = nodeB1;
   nodeB1->rightChild = nodeD1;
   nodeD1->linedef = &sectors[1].linedefs[3];
   nodeD1->subsector = nullptr;

   auto node9 = new BspNode;
   node9->isLeaf = true;
   node9->parent = nodeD1;
   nodeD1->rightChild = node9;
   node9->leftChild = nullptr;
   node9->rightChild = nullptr;
   node9->linedef = nullptr;
   node9->subsector = subsector9;

   auto node10 = new BspNode;
   node10->isLeaf = true;
   node10->parent = nodeD1;
   nodeD1->leftChild = node10;
   node10->leftChild = nullptr;
   node10->rightChild = nullptr;
   node10->linedef = nullptr;
   node10->subsector = subsector10;

   auto nodeA1 = new BspNode;
   nodeA1->isLeaf = false;
   nodeA1->parent = nodeB1;
   nodeB1->leftChild = nodeA1;
   nodeA1->linedef = &sectors[1].linedefs[0];
   nodeA1->subsector = nullptr;

   auto node11 = new BspNode;
   node11->isLeaf = true;
   node11->parent = nodeA1;
   nodeA1->rightChild = node11;
   node11->leftChild = nullptr;
   node11->rightChild = nullptr;
   node11->linedef = nullptr;
   node11->subsector = subsector11;

   auto node12 = new BspNode;
   node12->isLeaf = true;
   node12->parent = nodeA1;
   nodeA1->leftChild = node12;
   node12->leftChild = nullptr;
   node12->rightChild = nullptr;
   node12->linedef = nullptr;
   node12->subsector = subsector12;

   auto nodeC4 = new BspNode;
   nodeC4->isLeaf = false;
   nodeC4->parent = rootNode;
   rootNode->leftChild = nodeC4;
   nodeC4->linedef = &sectors[4].linedefs[2];
   nodeC4->subsector = nullptr;

   auto nodeG5 = new BspNode;
   nodeG5->isLeaf = false;
   nodeG5->parent = nodeC4;
   nodeC4->rightChild = nodeG5;
   nodeG5->linedef = &sectors[5].linedefs[6];
   nodeG5->subsector = nullptr;

   auto nodeD0 = new BspNode;
   nodeD0->isLeaf = false;
   nodeD0->parent = nodeG5;
   nodeG5->rightChild = nodeD0;
   nodeD0->linedef = &sectors[0].linedefs[3];
   nodeD0->subsector = nullptr;

   auto node13 = new BspNode;
   node13->isLeaf = true;
   node13->parent = nodeD0;
   nodeD0->rightChild = node13;
   node13->leftChild = nullptr;
   node13->rightChild = nullptr;
   node13->linedef = nullptr;
   node13->subsector = subsector13;

   auto node14 = new BspNode;
   node14->isLeaf = true;
   node14->parent = nodeD0;
   nodeD0->leftChild = node14;
   node14->leftChild = nullptr;
   node14->rightChild = nullptr;
   node14->linedef = nullptr;
   node14->subsector = subsector14;

   auto nodeH5 = new BspNode;
   nodeH5->isLeaf = false;
   nodeH5->parent = nodeG5;
   nodeG5->leftChild = nodeH5;
   nodeH5->linedef = &sectors[5].linedefs[7];
   nodeH5->subsector = nullptr;

   auto node15 = new BspNode;
   node15->isLeaf = true;
   node15->parent = nodeH5;
   nodeH5->rightChild = node15;
   node15->leftChild = nullptr;
   node15->rightChild = nullptr;
   node15->linedef = nullptr;
   node15->subsector = subsector15;

   auto nodeA5 = new BspNode;
   nodeA5->isLeaf = false;
   nodeA5->parent = nodeH5;
   nodeH5->leftChild = nodeA5;
   nodeA5->linedef = &sectors[5].linedefs[0];
   nodeA5->subsector = nullptr;

   auto node16 = new BspNode;
   node16->isLeaf = true;
   node16->parent = nodeH5;
   nodeA5->rightChild = node16;
   node16->leftChild = nullptr;
   node16->rightChild = nullptr;
   node16->linedef = nullptr;
   node16->subsector = subsector16;

   auto nodeB5 = new BspNode;
   nodeB5->isLeaf = false;
   nodeB5->parent = nodeA5;
   nodeA5->leftChild = nodeB5;
   nodeB5->linedef = &sectors[5].linedefs[1];
   nodeB5->subsector = nullptr;

   auto node17 = new BspNode;
   node17->isLeaf = true;
   node17->parent = nodeB5;
   nodeB5->rightChild = node17;
   node17->leftChild = nullptr;
   node17->rightChild = nullptr;
   node17->linedef = nullptr;
   node17->subsector = subsector17;

   auto nodeD5 = new BspNode;
   nodeD5->isLeaf = false;
   nodeD5->parent = nodeB5;
   nodeB5->leftChild = nodeD5;
   nodeD5->linedef = &sectors[5].linedefs[3];
   nodeD5->subsector = nullptr;

   auto node18 = new BspNode;
   node18->isLeaf = true;
   node18->parent = nodeD5;
   nodeD5->rightChild = node18;
   node18->leftChild = nullptr;
   node18->rightChild = nullptr;
   node18->linedef = nullptr;
   node18->subsector = subsector18;

   auto nodeE5 = new BspNode;
   nodeE5->isLeaf = false;
   nodeE5->parent = nodeD5;
   nodeD5->leftChild = nodeE5;
   nodeE5->linedef = &sectors[5].linedefs[4];
   nodeE5->subsector = nullptr;

   auto node19 = new BspNode;
   node19->isLeaf = true;
   node19->parent = nodeE5;
   nodeE5->rightChild = node19;
   node19->leftChild = nullptr;
   node19->rightChild = nullptr;
   node19->linedef = nullptr;
   node19->subsector = subsector19;

   auto node20 = new BspNode;
   node20->isLeaf = true;
   node20->parent = nodeE5;
   nodeE5->leftChild = node20;
   node20->leftChild = nullptr;
   node20->rightChild = nullptr;
   node20->linedef = nullptr;
   node20->subsector = subsector20;

   auto nodeD2 = new BspNode;
   nodeD2->isLeaf = false;
   nodeD2->parent = nodeC4;
   nodeC4->leftChild = nodeD2;
   nodeD2->linedef = &sectors[2].linedefs[3];
   nodeD2->subsector = nullptr;

   auto nodeC3 = new BspNode;
   nodeC3->isLeaf = false;
   nodeC3->parent = nodeD2;
   nodeD2->rightChild = nodeC3;
   nodeC3->linedef = &sectors[3].linedefs[2];
   nodeC3->subsector = nullptr;

   auto nodeC0 = new BspNode;
   nodeC0->isLeaf = false;
   nodeC0->parent = nodeC3;
   nodeC3->rightChild = nodeC0;
   nodeC0->linedef = &sectors[0].linedefs[2];
   nodeC0->subsector = nullptr;

   auto node21 = new BspNode;
   node21->isLeaf = true;
   node21->parent = nodeC0;
   nodeC0->rightChild = node21;
   node21->leftChild = nullptr;
   node21->rightChild = nullptr;
   node21->linedef = nullptr;
   node21->subsector = subsector21;

   auto node22 = new BspNode;
   node22->isLeaf = true;
   node22->parent = nodeC0;
   nodeC0->leftChild = node22;
   node22->leftChild = nullptr;
   node22->rightChild = nullptr;
   node22->linedef = nullptr;
   node22->subsector = subsector22;

   auto nodeB3 = new BspNode;
   nodeB3->isLeaf = false;
   nodeB3->parent = nodeC3;
   nodeC3->leftChild = nodeB3;
   nodeB3->linedef = &sectors[3].linedefs[1];
   nodeB3->subsector = nullptr;

   auto node23 = new BspNode;
   node23->isLeaf = true;
   node23->parent = nodeB3;
   nodeB3->rightChild = node23;
   node23->leftChild = nullptr;
   node23->rightChild = nullptr;
   node23->linedef = nullptr;
   node23->subsector = subsector23;

   auto nodeA3 = new BspNode;
   nodeA3->isLeaf = false;
   nodeA3->parent = nodeB3;
   nodeB3->leftChild = nodeA3;
   nodeA3->linedef = &sectors[3].linedefs[0];
   nodeA3->subsector = nullptr;

   auto node24 = new BspNode;
   node24->isLeaf = true;
   node24->parent = nodeA3;
   nodeA3->rightChild = node24;
   node24->leftChild = nullptr;
   node24->rightChild = nullptr;
   node24->linedef = nullptr;
   node24->subsector = subsector24;

   auto node25 = new BspNode;
   node25->isLeaf = true;
   node25->parent = nodeA3;
   nodeA3->leftChild = node25;
   node25->leftChild = nullptr;
   node25->rightChild = nullptr;
   node25->linedef = nullptr;
   node25->subsector = subsector25;

   auto nodeC2 = new BspNode;
   nodeC2->isLeaf = false;
   nodeC2->parent = nodeD2;
   nodeD2->leftChild = nodeC2;
   nodeC2->linedef = &sectors[2].linedefs[2];
   nodeC2->subsector = nullptr;

   auto nodeE4 = new BspNode;
   nodeE4->isLeaf = false;
   nodeE4->parent = nodeC2;
   nodeC2->rightChild = nodeE4;
   nodeE4->linedef = &sectors[4].linedefs[4];
   nodeE4->subsector = nullptr;

   auto node26 = new BspNode;
   node26->isLeaf = true;
   node26->parent = nodeE4;
   nodeE4->rightChild = node26;
   node26->leftChild = nullptr;
   node26->rightChild = nullptr;
   node26->linedef = nullptr;
   node26->subsector = subsector26;

   auto nodeB4 = new BspNode;
   nodeB4->isLeaf = false;
   nodeB4->parent = nodeE4;
   nodeE4->leftChild = nodeB4;
   nodeB4->linedef = &sectors[4].linedefs[1];
   nodeB4->subsector = nullptr;

   auto node27 = new BspNode;
   node27->isLeaf = true;
   node27->parent = nodeB4;
   nodeB4->rightChild = node27;
   node27->leftChild = nullptr;
   node27->rightChild = nullptr;
   node27->linedef = nullptr;
   node27->subsector = subsector27;

   auto node28 = new BspNode;
   node28->isLeaf = true;
   node28->parent = nodeB4;
   nodeB4->leftChild = node28;
   node28->leftChild = nullptr;
   node28->rightChild = nullptr;
   node28->linedef = nullptr;
   node28->subsector = subsector28;

   auto nodeB2 = new BspNode;
   nodeB2->isLeaf = false;
   nodeB2->parent = nodeC2;
   nodeC2->leftChild = nodeB2;
   nodeB2->linedef = &sectors[2].linedefs[1];
   nodeB2->subsector = nullptr;

   auto node29 = new BspNode;
   node29->isLeaf = true;
   node29->parent = nodeB2;
   nodeB2->rightChild = node29;
   node29->leftChild = nullptr;
   node29->rightChild = nullptr;
   node29->linedef = nullptr;
   node29->subsector = subsector29;

   auto node30 = new BspNode;
   node30->isLeaf = true;
   node30->parent = nodeB2;
   nodeB2->leftChild = node30;
   node30->leftChild = nullptr;
   node30->rightChild = nullptr;
   node30->linedef = nullptr;
   node30->subsector = subsector30;

   return rootNode;
}

#include "GameRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"
#include "DiagnosticsRenderer.h"
#include "IGameStateRenderer.h"

using namespace NAMESPACE;
using namespace std;

GameRenderer::GameRenderer( shared_ptr<RenderData> renderData,
                            shared_ptr<GameConfig> gameConfig,
                            shared_ptr<SFMLWindow> window,
                            shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                            shared_ptr<GameStateTracker> gameStateTracker ) :
   _renderData( renderData ),
   _gameConfig( gameConfig ),
   _window( window ),
   _diagnosticsRenderer( diagnosticsRenderer ),
   _gameStateTracker( gameStateTracker )
{
}

void GameRenderer::AddStateRenderer( GameState state, shared_ptr<IGameStateRenderer> renderer )
{
   _stateRendererMap[state] = renderer;
}

void GameRenderer::Initialize()
{
   _window->Initialize();
   _window->Show();
}

void GameRenderer::Render()
{
   _window->Clear();

   _stateRendererMap.at( _gameStateTracker->gameState )->Render();

   if ( _gameConfig->ShowDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _window->Render();
}

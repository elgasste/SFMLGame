#include "GameRenderer.h"
#include "RenderConfig.h"
#include "SFMLWindow.h"
#include "DiagnosticsRenderer.h"
#include "GameStateController.h"
#include "IGameStateRenderer.h"

using namespace NAMESPACE;
using namespace std;

GameRenderer::GameRenderer( shared_ptr<RenderConfig> renderConfig,
                            shared_ptr<SFMLWindow> window,
                            shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                            shared_ptr<GameStateController> stateController ) :
   _renderConfig( renderConfig ),
   _window( window ),
   _diagnosticsRenderer( diagnosticsRenderer ),
   _stateController( stateController )
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
   _window->HandleEvents();
   _window->Clear();

   _stateRendererMap.at( _stateController->GetState() )->Render();

   if ( _renderConfig->ShowDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _window->Render();
}

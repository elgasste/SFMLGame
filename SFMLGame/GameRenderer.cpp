#include "GameRenderer.h"
#include "GameConfig.h"
#include "GameStateProvider.h"
#include "SFMLWindow.h"
#include "DiagnosticsRenderer.h"
#include "IGameStateRenderer.h"

using namespace NAMESPACE;
using namespace std;

GameRenderer::GameRenderer( shared_ptr<GameConfig> config,
                            shared_ptr<GameStateProvider> gameStateProvider,
                            shared_ptr<SFMLWindow> window,
                            shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                            map<GameState, shared_ptr<IGameStateRenderer>> gameStateRenderers ) :
   _config( config ),
   _gameStateProvider( gameStateProvider ),
   _window( window ),
   _diagnosticsRenderer( diagnosticsRenderer ),
   _gameStateRenderers( gameStateRenderers )
{
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

   _gameStateRenderers.at( _gameStateProvider->GetState() )->Render();

   if ( _config->ShowDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _window->Render();
}

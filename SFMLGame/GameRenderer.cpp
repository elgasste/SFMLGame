#include "GameRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"
#include "DiagnosticsRenderer.h"
#include "ArenaRenderer.h"

using namespace NAMESPACE;
using namespace std;

GameRenderer::GameRenderer( shared_ptr<GameConfig> config,
                            shared_ptr<SFMLWindow> window,
                            shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                            shared_ptr<ArenaRenderer> arenaRenderer ) :
   _config( config ),
   _window( window ),
   _diagnosticsRenderer( diagnosticsRenderer ),
   _arenaRenderer( arenaRenderer )
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

   _arenaRenderer->Render();

   if ( _config->ShowDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _window->Render();
}

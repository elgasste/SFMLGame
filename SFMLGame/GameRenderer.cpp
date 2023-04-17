#include "GameRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"
#include "DiagnosticsRenderer.h"

using namespace NAMESPACE;
using namespace std;

GameRenderer::GameRenderer( shared_ptr<GameConfig> config,
                            shared_ptr<SFMLWindow> window,
                            shared_ptr<DiagnosticsRenderer> diagnosticsRenderer ) :
   _config( config ),
   _window( window ),
   _diagnosticsRenderer( diagnosticsRenderer )
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

   // TODO: draw the actual game right here

   if ( _config->ShowDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _window->Render();
}

#pragma once

#include <map>

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class RenderConfig;
class SFMLWindow;
class DiagnosticsRenderer;
class GameStateController;
class IGameStateRenderer;

class GameRenderer
{
public:
   GameRenderer( std::shared_ptr<RenderConfig> renderConfig,
                 std::shared_ptr<SFMLWindow> window,
                 std::shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                 std::shared_ptr<GameStateController> stateController );

   void AddStateRenderer( GameState state, std::shared_ptr<IGameStateRenderer> renderer );
   void Initialize();
   void Render();

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<DiagnosticsRenderer> _diagnosticsRenderer;
   std::shared_ptr<GameStateController> _stateController;

   std::map<GameState, std::shared_ptr<IGameStateRenderer>> _stateRendererMap;
};

NAMESPACE_END

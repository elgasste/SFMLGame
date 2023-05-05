#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class GameConfig;
class GameStateProvider;
class SFMLWindow;
class DiagnosticsRenderer;
class IGameStateRenderer;

class GameRenderer
{
public:
   GameRenderer( std::shared_ptr<GameConfig> config,
                 std::shared_ptr<GameStateProvider> gameStateProvider,
                 std::shared_ptr<SFMLWindow> window,
                 std::shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                 std::map<GameState, std::shared_ptr<IGameStateRenderer>> gameStateRenderers );

   void Initialize();
   void Render();

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<GameStateProvider> _gameStateProvider;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<DiagnosticsRenderer> _diagnosticsRenderer;

   std::map<GameState, std::shared_ptr<IGameStateRenderer>> _gameStateRenderers;
};

NAMESPACE_END

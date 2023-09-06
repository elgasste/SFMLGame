#pragma once

#include "Common.h"
#include "GameStateTracker.h"

NAMESPACE_BEGIN

class GameConfig;
class SFMLWindow;
class DiagnosticsRenderer;
class GameStateController;
class IGameStateRenderer;

class GameRenderer
{
public:
   GameRenderer( std::shared_ptr<GameConfig> gameConfig,
                 std::shared_ptr<SFMLWindow> window,
                 std::shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                 std::shared_ptr<GameStateTracker> gameStateTracker );

   void AddStateRenderer( GameState state, std::shared_ptr<IGameStateRenderer> renderer );
   void Initialize();
   void Render();

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<DiagnosticsRenderer> _diagnosticsRenderer;
   std::shared_ptr<GameStateTracker> _gameStateTracker;

   std::map<GameState, std::shared_ptr<IGameStateRenderer>> _stateRendererMap;
};

NAMESPACE_END

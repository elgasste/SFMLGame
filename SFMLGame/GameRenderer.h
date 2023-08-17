#pragma once

#include "Common.h"
#include "GameState.h"

NAMESPACE_BEGIN

class RenderData;
class GameConfig;
class GameData;
class SFMLWindow;
class DiagnosticsRenderer;
class GameStateController;
class IGameStateRenderer;

class GameRenderer
{
public:
   GameRenderer( std::shared_ptr<RenderData> renderData,
                 std::shared_ptr<GameConfig> gameConfig,
                 std::shared_ptr<GameData> gameData,
                 std::shared_ptr<SFMLWindow> window,
                 std::shared_ptr<DiagnosticsRenderer> diagnosticsRenderer );

   void AddStateRenderer( GameState state, std::shared_ptr<IGameStateRenderer> renderer );
   void Initialize();
   void Render();

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<DiagnosticsRenderer> _diagnosticsRenderer;

   std::map<GameState, std::shared_ptr<IGameStateRenderer>> _stateRendererMap;
};

NAMESPACE_END

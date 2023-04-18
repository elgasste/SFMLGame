#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;
class SFMLWindow;
class DiagnosticsRenderer;
class ArenaRenderer;

class GameRenderer
{
public:
   GameRenderer( std::shared_ptr<GameConfig> config,
                 std::shared_ptr<SFMLWindow> window,
                 std::shared_ptr<DiagnosticsRenderer> diagnosticsRenderer,
                 std::shared_ptr<ArenaRenderer> arenaRenderer );

   void Initialize();
   void Render();

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<DiagnosticsRenderer> _diagnosticsRenderer;
   std::shared_ptr<ArenaRenderer> _arenaRenderer;
};

NAMESPACE_END

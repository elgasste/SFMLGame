#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class RenderConfig;
class RenderData;
class GameConfig;
class GameData;
class SFMLWindow;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                         std::shared_ptr<RenderData> renderData,
                         std::shared_ptr<GameConfig> gameConfig,
                         std::shared_ptr<GameData> gameData,
                         std::shared_ptr<SFMLWindow> window );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<SFMLWindow> _window;

   sf::RectangleShape _backgroundRect;
};

NAMESPACE_END

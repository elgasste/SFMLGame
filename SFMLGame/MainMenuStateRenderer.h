#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class RenderConfig;
class RenderData;
class SFMLWindow;
class GameClock;
class MainMenu;

class MainMenuStateRenderer : public IGameStateRenderer
{
public:
   MainMenuStateRenderer( std::shared_ptr<GameConfig> gameConfig,
                          std::shared_ptr<GameData> gameData,
                          std::shared_ptr<RenderConfig> renderConfig,
                          std::shared_ptr<RenderData> renderData,
                          std::shared_ptr<SFMLWindow> window,
                          std::shared_ptr<GameClock> clock,
                          std::shared_ptr<MainMenu> menu );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<MainMenu> _menu;

   sf::RectangleShape _backgroundRect;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
   std::shared_ptr<sf::Text> _carat;

   float _menuX;
   float _menuY;
   float _lineSpacing;

   float _elapsedSeconds;
   bool _showCarat;

   sf::Sprite _ballSprite;
};

NAMESPACE_END

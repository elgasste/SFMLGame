#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

namespace sf
{
   class Font;
   class Text;
   class RectangleShape;
}

NAMESPACE_BEGIN

class RenderConfig;
class SFMLWindow;
class GameClock;
class MainMenu;

class MainMenuStateRenderer : public IGameStateRenderer
{
public:
   MainMenuStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                          std::shared_ptr<SFMLWindow> window,
                          std::shared_ptr<GameClock> clock,
                          std::shared_ptr<MainMenu> menu );

   // IGameStateRenderer
   void Render() override;

private:
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

   int _currentOptionIndexCache;
   float _elapsedSeconds;
   bool _showCarat;
};

NAMESPACE_END

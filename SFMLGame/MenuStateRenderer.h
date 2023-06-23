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

class GameConfig;
class SFMLWindow;
class GameClock;
class Menu;

class MenuStateRenderer : public IGameStateRenderer
{
public:
   MenuStateRenderer( std::shared_ptr<GameConfig> config,
                      std::shared_ptr<SFMLWindow> window,
                      std::shared_ptr<GameClock> clock,
                      std::shared_ptr<Menu> menu );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Menu> _menu;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
   std::shared_ptr<sf::Text> _carat;

   float _menuX;
   float _menuY;
   float _lineSpacing;

   float _elapsedSeconds;
   bool _showCarat;
};

NAMESPACE_END

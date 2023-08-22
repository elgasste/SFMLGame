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
class PlayingStateMenu;

class MenuStateRenderer : public IGameStateRenderer
{
public:
   MenuStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                      std::shared_ptr<SFMLWindow> window,
                      std::shared_ptr<GameClock> clock,
                      std::shared_ptr<PlayingStateMenu> menu );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<PlayingStateMenu> _menu;

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

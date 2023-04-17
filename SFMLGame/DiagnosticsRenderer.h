#pragma once

#include "Common.h"

namespace sf
{
   class Font;
   class Text;
   class RectangleShape;
}

NAMESPACE_BEGIN

class GameConfig;
class GameClock;
class SFMLWindow;

class DiagnosticsRenderer
{
public:
   DiagnosticsRenderer( std::shared_ptr<GameConfig> config,
                        std::shared_ptr<GameClock> clock,
                        std::shared_ptr<SFMLWindow> window );

   void Render();

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<SFMLWindow> _window;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
   std::shared_ptr<sf::RectangleShape> _background;
};

NAMESPACE_END

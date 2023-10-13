#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig;
class GameData;
class GameClock;
class SFMLWindow;

class DiagnosticsRenderer
{
public:
   DiagnosticsRenderer( std::shared_ptr<RenderConfig> renderConfig,
                        std::shared_ptr<GameData> gameData,
                        std::shared_ptr<GameClock> clock,
                        std::shared_ptr<SFMLWindow> window );

   void Render();

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<SFMLWindow> _window;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
   std::shared_ptr<sf::RectangleShape> _background;

   unsigned int _currentFrameRateCache;
   float _elapsedSeconds;
};

NAMESPACE_END

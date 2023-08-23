#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class RenderConfig;
class SFMLWindow;
class GameClock;
class TitleMenu;

class TitleMenuStateRenderer : public IGameStateRenderer
{
public:
   TitleMenuStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                           std::shared_ptr<SFMLWindow> window,
                           std::shared_ptr<GameClock> clock,
                           std::shared_ptr<TitleMenu> menu );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<TitleMenu> _menu;

   sf::RectangleShape _backgroundRect;

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

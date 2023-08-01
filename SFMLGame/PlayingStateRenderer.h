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
class RenderConfig;
class SFMLWindow;
class BspOperator;
class Entity;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<GameConfig> gameConfig,
                         std::shared_ptr<RenderConfig> renderConfig,
                         std::shared_ptr<SFMLWindow> window,
                         std::shared_ptr<BspOperator> bspOperator,
                         std::shared_ptr<Entity> player );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<BspOperator> _bspOperator;
   std::shared_ptr<Entity> _player;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
};

NAMESPACE_END

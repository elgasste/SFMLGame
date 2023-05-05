#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

namespace sf
{
   class Font;
   class Text;
}

NAMESPACE_BEGIN

class GameConfig;
class SFMLWindow;

class LoadingStateRenderer : public IGameStateRenderer
{
public:
   LoadingStateRenderer( std::shared_ptr<GameConfig> config,
                         std::shared_ptr<SFMLWindow> window );

   void Render() override;

private:
   std::shared_ptr<SFMLWindow> _window;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
};

NAMESPACE_END

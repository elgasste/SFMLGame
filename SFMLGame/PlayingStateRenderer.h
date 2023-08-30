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
class RaycastRenderer;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                         std::shared_ptr<SFMLWindow> window,
                         std::shared_ptr<RaycastRenderer> raycastRenderer );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<RaycastRenderer> _raycastRenderer;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class RenderConfig;
class SFMLWindow;

class TitleScreenStateRenderer : public IGameStateRenderer
{
public:
   TitleScreenStateRenderer( std::shared_ptr<RenderConfig> renderConfig,
                             std::shared_ptr<SFMLWindow> window );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<SFMLWindow> _window;

   std::shared_ptr<sf::Font> _font;
   std::shared_ptr<sf::Text> _text;
};

NAMESPACE_END

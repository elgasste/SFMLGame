#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class RenderData;
class SFMLWindow;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<RenderData> renderData,
                         std::shared_ptr<SFMLWindow> window );

   void Render() override;

private:
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<SFMLWindow> _window;
};

NAMESPACE_END

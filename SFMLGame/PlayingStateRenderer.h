#pragma once

#include "Common.h"
#include "IGameStateRenderer.h"

NAMESPACE_BEGIN

class GameConfig;
class WireframeMapRenderer;
class DetailedMapRenderer;

class PlayingStateRenderer : public IGameStateRenderer
{
public:
   PlayingStateRenderer( std::shared_ptr<GameConfig> gameConfig,
                         std::shared_ptr<WireframeMapRenderer> wireframeMapRenderer,
                         std::shared_ptr<DetailedMapRenderer> detailedMapRenderer );

   // IGameStateRenderer
   void Render() override;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<WireframeMapRenderer> _wireframeMapRenderer;
   std::shared_ptr<DetailedMapRenderer> _detailedMapRenderer;
};

NAMESPACE_END

#pragma once

#include <SFML/Graphics/Vertex.hpp>

#include "Common.h"
#include "Lineseg.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;
class Entity;
class SFMLWindow;

class RaycastRenderer
{
public:
   RaycastRenderer( std::shared_ptr<GameConfig> gameConfig,
                    std::shared_ptr<RenderConfig> renderConfig,
                    std::shared_ptr<Entity> player,
                    std::shared_ptr<SFMLWindow> window );

   void RenderCeilingAndFloor();
   void RenderLineseg( const Lineseg& lineseg,
                       float drawStartAngle,
                       int startColumn,
                       int endColumn );

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<Entity> _player;
   std::shared_ptr<SFMLWindow> _window;

   // MUFFINS: this should change with config->ScreenWidth, figure that one out
   sf::Vertex _renderColumns[1920 * 2];
   sf::Vertex _ceilingRenderRect[4];
   sf::Vertex _floorRenderRect[4];
};

NAMESPACE_END

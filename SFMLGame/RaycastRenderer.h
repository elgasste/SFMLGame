#pragma once

#include <SFML/Graphics/Vertex.hpp>

#include "Common.h"
#include "Lineseg.h"

NAMESPACE_BEGIN

class GameConfig;
class Entity;
class SFMLWindow;

class RaycastRenderer
{
public:
   RaycastRenderer( std::shared_ptr<GameConfig> config,
                    std::shared_ptr<Entity> player,
                    std::shared_ptr<SFMLWindow> window );

   void RenderCeilingAndFloor();
   void RenderLineseg( const Lineseg& lineseg,
                       float drawStartAngle,
                       int startColumn,
                       int endColumn );

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<Entity> _player;
   std::shared_ptr<SFMLWindow> _window;

   // MUFFINS: this should change with config->ScreenWidth, figure that one out
   sf::Vertex _renderColumns[1920 * 2];
   sf::Vertex _ceilingRenderRect[4];
   sf::Vertex _floorRenderRect[4];

   float _wallHeight;
   float _projectionPlaneDelta;
};

NAMESPACE_END

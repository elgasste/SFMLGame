#pragma once

#include <SFML/Graphics/Vertex.hpp>

#include "Common.h"
#include "Lineseg.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;
class GameData;
class RenderData;
class SFMLWindow;

class RaycastRenderer
{
public:
   RaycastRenderer( std::shared_ptr<GameConfig> gameConfig,
                    std::shared_ptr<RenderConfig> renderConfig,
                    std::shared_ptr<GameData> gameData,
                    std::shared_ptr<RenderData> renderData,
                    std::shared_ptr<SFMLWindow> window );
   ~RaycastRenderer();

   void RenderCeilingAndFloor();
   void RenderLineseg( const Lineseg& lineseg,
                       float drawStartAngle,
                       int startColumn,
                       int endColumn );

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderData> _renderData;
   std::shared_ptr<SFMLWindow> _window;

   sf::Vertex* _renderColumns;
   sf::Vertex _floorRenderRect[4];

   sf::Vector2f _skyPosition;
   sf::IntRect _skyTextureRect;
   float _skyTextureScalar;

   sf::Vector2f _spritePosition;
   sf::IntRect _spriteTextureRect;
   sf::Vector2f _spriteVerticalScale;
};

NAMESPACE_END

#pragma once

#include <SFML/Graphics.hpp>

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class GameConfig;
class GameData;
class RenderConfig;
class SFMLWindow;
class ColumnTracker;

class TopDownRenderer
{
public:
   TopDownRenderer( std::shared_ptr<GameConfig> gameConfig,
                    std::shared_ptr<GameData> gameData,
                    std::shared_ptr<RenderConfig> renderConfig,
                    std::shared_ptr<SFMLWindow> window,
                    std::shared_ptr<ColumnTracker> columnTracker );

   void Render();

private:
   void RenderSectors();
   void RenderFovRecursive( BspNode* node );
   void RenderLeaf( BspNode* leaf );
   void RenderLineseg( const Lineseg& lineseg,
                       float drawStartAngle,
                       int startColumn,
                       int endColumn );

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<GameData> _gameData;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<SFMLWindow> _window;
   std::shared_ptr<ColumnTracker> _columnTracker;

   sf::VertexArray _linesegDrawer;
   sf::CircleShape _playerDrawer;
   sf::VertexArray _playerFovDrawer;
   
   sf::Vector2f _viewOrigin;
   float _leftFovAngle;
};

NAMESPACE_END

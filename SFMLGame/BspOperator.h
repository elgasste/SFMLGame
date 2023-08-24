#pragma once


#include "Common.h"
#include "Geometry.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;
class Entity;
class RaycastRenderer;
class ColumnTracker;

class BspOperator
{
public:
   BspOperator( std::shared_ptr<GameConfig> gameConfig,
                std::shared_ptr<RenderConfig> renderConfig,
                std::shared_ptr<RaycastRenderer> raycastRenderer,
                std::shared_ptr<ColumnTracker> columnTracker,
                BspNode* rootNode );
   ~BspOperator();

   const Subsector& GetOccupyingSubsector( std::shared_ptr<Entity> entity ) const;
   void RenderWorld( std::shared_ptr<Entity> viewingEntity );
   bool CheckWallCollision( float startX, float startY, float endX, float endY ) const;

private:
   void DeleteTreeRecursive( BspNode* node );
   void RenderNodeRecursive( BspNode* node );
   void RenderLeaf( BspNode* leaf );
   bool CheckWallNodeCollisionRecursive( BspNode* node, float startX, float startY, float endX, float endY ) const;

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<RaycastRenderer> _raycastRenderer;
   std::shared_ptr<ColumnTracker> _columnTracker;
   BspNode* _rootNode;

   sf::Vector2f _viewOrigin;
   float _leftFovAngle;
};

NAMESPACE_END

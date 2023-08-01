#pragma once

#include <vector>

#include "Common.h"
#include "Geometry.h"
#include "BspNode.h"
#include "Range.h"

NAMESPACE_BEGIN

class GameConfig;
class RenderConfig;
class Entity;
class RaycastRenderer;

class BspOperator
{
public:
   BspOperator( std::shared_ptr<GameConfig> gameConfig,
                std::shared_ptr<RenderConfig> renderConfig,
                std::shared_ptr<RaycastRenderer> raycastRenderer,
                BspNode* rootNode );
   ~BspOperator();

   const Subsector& GetOccupyingSubsector( std::shared_ptr<Entity> entity );
   void RenderWorld( std::shared_ptr<Entity> viewingEntity );

private:
   void DeleteTreeRecursive( BspNode* node );
   void RenderNodeRecursive( BspNode* node );
   void RenderLeaf( BspNode* leaf );
   void MarkRangeAsDrawn( int start, int end );

private:
   std::shared_ptr<GameConfig> _gameConfig;
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<RaycastRenderer> _raycastRenderer;
   BspNode* _rootNode;

   std::vector<Range<int>> _undrawnRanges;

   sf::Vector2f _viewOrigin;
   float _leftFovAngle;
};

NAMESPACE_END

#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class GameConfig;
class Entity;

class BspRenderer
{
public:
   BspRenderer( std::shared_ptr<GameConfig> config, BspNode* rootNode );
   ~BspRenderer();

   void Traverse( std::shared_ptr<Entity> entity );

private:
   void DeleteTreeRecursive( BspNode* node );
   void CheckNodeRecursive( BspNode* node );
   void CheckLeaf( BspNode* leaf );
   int CloseFovSegment( int index, float startAngle, float endAngle );

private:
   BspNode* _rootNode;
   std::shared_ptr<Entity> _entity;

   std::vector<sf::Vector2f> _fovSegments;
   float _rayIncrement;
};

NAMESPACE_END

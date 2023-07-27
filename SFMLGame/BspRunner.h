#pragma once

#include <vector>

#include "Common.h"
#include "Geometry.h"
#include "BspNode.h"
#include "Range.h"

NAMESPACE_BEGIN

class GameConfig;
class Entity;
class RaycastRenderer;

class BspRunner
{
public:
   BspRunner( std::shared_ptr<GameConfig> config,
              std::shared_ptr<Entity> player,
              std::shared_ptr<RaycastRenderer> renderer,
              BspNode* rootNode );
   ~BspRunner();

   void DeleteTreeRecursive( BspNode* node );
   void Run();

   // MUFFINS
   const std::vector<int>& GetGeometryCheckList() { return _geometryCheckList; }

private:
   const float FovRange = RAD_30 * 2.0f;

   void CheckNodeRecursive( BspNode* node );
   void CheckLeaf( BspNode* leaf );
   void MarkRangeAsDrawn( int start, int end );

private:
   std::shared_ptr<GameConfig> _config;
   std::shared_ptr<Entity> _player;
   std::shared_ptr<RaycastRenderer> _renderer;
   BspNode* _rootNode;

   std::vector<Range<int>> _undrawnRanges;

   sf::Vector2f _origin;
   float _leftFovAngle;
   float _fovAngleIncrement;

   // MUFFINS: for diagnostics
   int _treeDepth;
   int _maxTreeDepth;
   float _angleOfMaxTreeDepth;
   int _linesegsDrawn;
   int _maxLinesegsDrawn;
   float _angleOfMaxLinesegsDrawn;
   int _geometryChecks;
   int _maxGeometryChecks;
   float _angleOfMaxGeometryChecks;
   std::vector<int> _geometryCheckList;
};

NAMESPACE_END

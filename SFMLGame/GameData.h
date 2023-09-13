#pragma once

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<std::vector<LineDef>> lineDefs,
             std::shared_ptr<std::vector<SubSector>> subSectors,
             BspNode* rootBspNode,
             std::shared_ptr<Entity> player );
   ~GameData();

   const std::vector<LineDef>& GetLineDefs() { return *_lineDefs; }
   BspNode* GetRootBspNode() const { return _rootBspNode; }
   std::shared_ptr<Entity> GetPlayer() const { return _player; }

private:
   void DeleteBspNodeRecursive( BspNode* node );

private:
   std::shared_ptr<std::vector<LineDef>> _lineDefs;
   std::shared_ptr<std::vector<SubSector>> _subSectors;
   BspNode* _rootBspNode;
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END

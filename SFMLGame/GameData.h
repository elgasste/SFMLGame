#pragma once

#include "Common.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<std::vector<Linedef>> linedefs,
             BspNode* rootBspNode,
             std::shared_ptr<Entity> player );
   ~GameData();

   const std::vector<Linedef>& GetLinedefs() { return *_linedefs; }
   BspNode* GetRootBspNode() const { return _rootBspNode; }
   std::shared_ptr<Entity> GetPlayer() const { return _player; }

private:
   void DeleteBspNodeRecursive( BspNode* node );

private:
   std::shared_ptr<std::vector<Linedef>> _linedefs;
   BspNode* _rootBspNode;
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END

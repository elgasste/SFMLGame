#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"
#include "BspNode.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::shared_ptr<std::vector<Sector>> sectors,
             BspNode* bspRootNode,
             std::shared_ptr<Entity> player );
   ~GameData();

   std::shared_ptr<std::vector<Sector>> GetSectors() { return _sectors; }
   BspNode* GetBspRootNode() { return _bspRootNode; }
   std::shared_ptr<Entity> GetPlayer() { return _player; }

private:
   void DeleteBspTreeRecursive( BspNode* node );

private:
   std::shared_ptr<std::vector<Sector>> _sectors;
   BspNode* _bspRootNode;
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END

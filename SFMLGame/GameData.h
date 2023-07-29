#pragma once

#include <vector>

#include "Common.h"
#include "Sector.h"

NAMESPACE_BEGIN

class Entity;

class GameData
{
public:
   GameData( std::vector<Sector> sectors,
             std::shared_ptr<Entity> player );

   std::vector<Sector>& GetSectors() { return _sectors; }
   std::shared_ptr<Entity> GetPlayer() { return _player; }

private:
   std::vector<Sector> _sectors;
   std::shared_ptr<Entity> _player;
};

NAMESPACE_END

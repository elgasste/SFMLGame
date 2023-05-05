#pragma once

#include "Entity.h"

NAMESPACE_BEGIN

class UniqueNumberGenerator;
class GameData;

class Player : public Entity
{
public:
   Player( std::shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator,
           std::shared_ptr<GameData> gameData );
};

NAMESPACE_END

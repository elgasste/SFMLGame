#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class Game;

class GameLoader
{
public:
   std::shared_ptr<Game> Load();
};

NAMESPACE_END

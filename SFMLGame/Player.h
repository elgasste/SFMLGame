#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Common.h"
#include "Actor.h"

NAMESPACE_BEGIN

class GameData;

class Player : public Actor
{
public:
   Player( std::shared_ptr<GameData> gameData );
};

NAMESPACE_END

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class GameConfig;

class GameData
{
public:
   GameData( std::shared_ptr<GameConfig> config );

public:
   sf::FloatRect ArenaBounds;

   sf::FloatRect PlayerHitBox;
   sf::Vector2f PlayerDefaultPosition;
   float PlayerMoveVelocity;
   Direction PlayerDefaultDirection;
};

NAMESPACE_END

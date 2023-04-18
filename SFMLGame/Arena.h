#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class GameData;
class GameClock;
class Player;

class Arena
{
public:
   Arena( std::shared_ptr<GameData> gameData,
          std::shared_ptr<GameClock> clock,
          std::shared_ptr<Player> player );

   std::shared_ptr<Player> GetPlayer() { return _player; }

   sf::FloatRect GetBounds() const { return _bounds; }
   void SetBounds( const sf::FloatRect& bounds ) { _bounds = bounds; }

   void Tick();

private:
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Player> _player;

   sf::FloatRect _bounds;
};

NAMESPACE_END

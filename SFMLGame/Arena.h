#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class GameData;
class GameClock;
class Player;
class Entity;
class Actor;

class Arena
{
public:
   Arena( std::shared_ptr<GameData> gameData,
          std::shared_ptr<GameClock> clock,
          std::shared_ptr<Player> player );

   std::shared_ptr<Player> GetPlayer() { return _player; }

   sf::FloatRect GetBounds() const { return _bounds; }
   void SetBounds( const sf::FloatRect& bounds ) { _bounds = bounds; }

   void AddActor( std::shared_ptr<Actor> actor );
   void RemoveActor( unsigned int uniqueId );

   void Tick();

private:
   void MoveEntity( std::shared_ptr<Entity> entity ) const;

private:
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Player> _player;

   sf::FloatRect _bounds;

   std::vector<std::shared_ptr<Actor>> _actors;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class RenderConfig;
class GameClock;
class Entity;

class EntitySprite
{
public:
   EntitySprite( std::shared_ptr<RenderConfig> renderConfig,
                 std::shared_ptr<GameClock> gameClock,
                 std::shared_ptr<Entity> entity,
                 std::shared_ptr<sf::Texture> texture,
                 sf::Vector2i size,
                 sf::Vector2f origin,
                 int movementFrames );

   void SetPosition( const sf::Vector2f& position );

   const sf::Sprite& GetSprite();

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameClock> _gameClock;
   std::shared_ptr<Entity> _entity;

   sf::Sprite _sprite;
   sf::Vector2i _size;

   sf::IntRect _textureRect;
   std::map<Direction, int> _directionOffsetMap;
   int _movementFrames;
   int _currentMovementFrame;
   float _elapsedMovementTime;
};

NAMESPACE_END

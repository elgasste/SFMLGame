#pragma once

#include "Common.h"
#include "Direction.h"
#include "EntitySpriteLayer.h"

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
                 std::shared_ptr<std::map<EntitySpriteLayer, std::shared_ptr<sf::Texture>>> textureLayerMap,
                 sf::Vector2i spriteSize,
                 sf::Vector2f origin,
                 int movementFrames );

   void Tick();
   void SetPosition( const sf::Vector2f& position );
   bool HasLayer( EntitySpriteLayer layer ) const { return _spriteLayerMap.find( layer ) != _spriteLayerMap.end(); }
   const sf::Sprite& GetSpriteForLayer( EntitySpriteLayer layer ) const { return _spriteLayerMap.at( layer ); }
   void RemoveLayer( EntitySpriteLayer layer );

private:
   std::shared_ptr<RenderConfig> _renderConfig;
   std::shared_ptr<GameClock> _gameClock;
   std::shared_ptr<Entity> _entity;

   //std::shared_ptr<std::map<EntitySpriteLayer, std::shared_ptr<sf::Texture>>> _textureLayerMap;
   std::map<EntitySpriteLayer, sf::Sprite> _spriteLayerMap;
   sf::Vector2i _spriteSize;

   sf::IntRect _textureRect;
   std::map<Direction, int> _directionOffsetMap;
   int _movementFrames;
   int _currentMovementFrame;
   float _elapsedMovementTime;
};

NAMESPACE_END

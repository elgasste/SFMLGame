#include "EntitySprite.h"
#include "RenderConfig.h"
#include "GameClock.h"
#include "Entity.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

EntitySprite::EntitySprite( shared_ptr<RenderConfig> renderConfig,
                            shared_ptr<GameClock> gameClock,
                            shared_ptr<Entity> entity,
                            shared_ptr<map<EntitySpriteLayer, shared_ptr<Texture>>> textureLayerMap,
                            Vector2i spriteSize,
                            Vector2f origin,
                            int movementFrames ) :
   _renderConfig( renderConfig ),
   _entity( entity ),
   _gameClock( gameClock ),
   _spriteSize( spriteSize ),
   _movementFrames( movementFrames ),
   _currentMovementFrame( 1 ),
   _elapsedMovementTime( 0 )
{
   _textureRect = { 0, 0, spriteSize.x, spriteSize.y };

   for ( map<EntitySpriteLayer, shared_ptr<Texture>>::iterator it = textureLayerMap->begin(); it != textureLayerMap->end(); it++ )
   {
      _spriteLayerMap[it->first] = Sprite( *( it->second ) );

      _spriteLayerMap.at( it->first ).setTextureRect( _textureRect );
      _spriteLayerMap.at( it->first ).setOrigin( origin );
   }

   _directionOffsetMap =
   {
      { Direction::Up, 0 },
      { Direction::Left, spriteSize.y },
      { Direction::Down, 2 * spriteSize.y },
      { Direction::Right, 3 * spriteSize.y }
   };
}

void EntitySprite::Tick()
{
   _textureRect.top = _directionOffsetMap.at( _entity->GetDirection() );

   if ( _entity->IsMoving() )
   {
      _elapsedMovementTime += _gameClock->GetFrameSeconds();

      if ( _elapsedMovementTime > _renderConfig->PlayerSpriteFrameIncrement )
      {
         _elapsedMovementTime = 0;
         _currentMovementFrame++;

         if ( _currentMovementFrame > _movementFrames )
         {
            _currentMovementFrame = 1;
         }
      }

      // all frames after frame 0 are "walking" frames
      _textureRect.left = _currentMovementFrame * _spriteSize.x;
   }
   else
   {
      // frame 0 is the "standing" frame
      _elapsedMovementTime = 0;
      _textureRect.left = 0;
   }

   for ( map<EntitySpriteLayer, Sprite>::iterator it = _spriteLayerMap.begin(); it != _spriteLayerMap.end(); it++ )
   {
      _spriteLayerMap.at( it->first ).setTextureRect( _textureRect );
   }
}

void EntitySprite::SetPosition( const sf::Vector2f& position )
{
   for ( map<EntitySpriteLayer, Sprite>::iterator it = _spriteLayerMap.begin(); it != _spriteLayerMap.end(); it++ )
   {
      _spriteLayerMap.at( it->first ).setPosition( position );
   }
}

void EntitySprite::RemoveLayer( EntitySpriteLayer layer )
{
   if ( HasLayer( layer ) )
   {
      _spriteLayerMap.erase( layer );
   }
}

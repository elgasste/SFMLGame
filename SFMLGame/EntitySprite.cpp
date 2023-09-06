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
                            shared_ptr<Texture> texture,
                            Vector2i size,
                            Vector2f origin,
                            int movementFrames ) :
   _renderConfig( renderConfig ),
   _entity( entity ),
   _gameClock( gameClock ),
   _size( size ),
   _movementFrames( movementFrames ),
   _currentMovementFrame( 1 ),
   _elapsedMovementTime( 0 )
{
   _textureRect = { 0, 0, size.x, size.y };

   _sprite = Sprite( *texture );
   _sprite.setTextureRect( _textureRect );
   _sprite.setScale( renderConfig->SpriteScalar, renderConfig->SpriteScalar );
   _sprite.setOrigin( origin );

   _directionOffsetMap =
   {
      { Direction::Up, 0 },
      { Direction::Left, size.y },
      { Direction::Down, 2 * size.y },
      { Direction::Right, 3 * size.y }
   };
}

void EntitySprite::SetPosition( const sf::Vector2f& position )
{
   _sprite.setPosition( position );
}

const Sprite& EntitySprite::GetSprite()
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
      _textureRect.left = _currentMovementFrame * _size.x;
   }
   else
   {
      // frame 0 is the "standing" frame
      _elapsedMovementTime = 0;
      _textureRect.left = 0;
   }

   _sprite.setTextureRect( _textureRect );
   return _sprite;
}

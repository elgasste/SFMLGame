#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "ActorSprite.h"
#include "GameClock.h"
#include "Actor.h"
#include "Direction.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

ActorSprite::ActorSprite( shared_ptr<GameClock> clock,
                          shared_ptr<Actor> actor,
                          shared_ptr<Texture> texture,
                          Vector2i frameDimensions,
                          int totalMovingFrames,
                          float secondsPerFrame ) :
   _clock( clock ),
   _actor( actor ),
   _texture( texture ),
   _frameDimensions( frameDimensions ),
   _totalMovingFrames( totalMovingFrames ),
   _secondsPerFrame( secondsPerFrame )
{
   _sprite = make_shared<Sprite>();
   _sprite->setTexture( *texture );
   _sprite->setTextureRect( IntRect( 0, 0, frameDimensions.x, frameDimensions.y ) );

   _currentMovingFrame = 1;
   _elapsedMovingSeconds = 0;
}

void ActorSprite::Tick()
{
   _sprite->setPosition( _actor->GetPosition() );

   auto actorVelocity = _actor->GetVelocity();

   // the texture should have four lanes, each directly tied to a direction
   auto lane = (int)_actor->GetDirection();

   if ( actorVelocity.x == 0 && actorVelocity.y == 0 )
   {
      // the first frame of each lane is the static texture
      _sprite->setTextureRect( IntRect( 0, lane * _frameDimensions.y, _frameDimensions.x, _frameDimensions.y ) );

      _currentMovingFrame = 1;
      _elapsedMovingSeconds = 0;
   }
   else
   {
      // all frames after the first frame are for movement
      _sprite->setTextureRect( IntRect( _currentMovingFrame * _frameDimensions.x,
                                        lane * (int)_frameDimensions.y,
                                        _frameDimensions.x,
                                        _frameDimensions.y ) );

      _elapsedMovingSeconds += _clock->GetFrameSeconds();

      if ( _elapsedMovingSeconds >= _secondsPerFrame )
      {
         _elapsedMovingSeconds = 0;
         _currentMovingFrame++;

         if ( _currentMovingFrame > _totalMovingFrames )
         {
            _currentMovingFrame = 1;
         }
      }
   }
}

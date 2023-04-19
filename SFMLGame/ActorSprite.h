#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"

namespace sf
{
   class Texture;
   class Sprite;
}

NAMESPACE_BEGIN

class GameClock;
class Actor;

class ActorSprite
{
public:
   ActorSprite( std::shared_ptr<GameClock> clock,
                std::shared_ptr<Actor> actor,
                std::shared_ptr<sf::Texture> texture,
                sf::Vector2i frameDimensions,
                int totalMovingFrames,
                float secondsPerFrame );

   std::shared_ptr<sf::Sprite> GetSprite() { return _sprite; }

   void Tick();

private:
   std::shared_ptr<GameClock> _clock;
   std::shared_ptr<Actor> _actor;

   std::shared_ptr<sf::Texture> _texture;
   std::shared_ptr<sf::Sprite> _sprite;
   sf::Vector2i _frameDimensions;

   int _totalMovingFrames;
   int _currentMovingFrame;
   float _secondsPerFrame;
   float _elapsedMovingSeconds;
};

NAMESPACE_END

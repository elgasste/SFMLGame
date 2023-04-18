#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class GameData;

class Player
{
public:
   Player( std::shared_ptr<GameData> gameData );

   sf::Vector2f GetPosition() const { return _position; }
   void SetPosition( const sf::Vector2f& position ) { _position = position; }
   void SetPositionX( float position ) { _position.x = position; }
   void SetPositionY( float position ) { _position.y = position; }

   sf::FloatRect GetHitBox() const { return _hitBox; }
   void SetHitBox( const sf::FloatRect& hitBox ) { _hitBox = hitBox; }

   sf::Vector2f GetVelocity() const { return _velocity; }
   void SetVelocityX( float velocity ) { _velocity.x = velocity; }
   void SetVelocityY( float velocity ) { _velocity.y = velocity; }

   Direction GetDirection() const { return _direction; }
   void SetDirection( Direction direction ) { _direction = direction; }

   void MoveX( float distanceX );
   void MoveY( float distanceY );

private:
   sf::Vector2f _position;
   sf::FloatRect _hitBox;
   sf::Vector2f _velocity;
   Direction _direction;
};

NAMESPACE_END

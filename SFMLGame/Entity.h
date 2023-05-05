#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Common.h"
#include "Direction.h"

NAMESPACE_BEGIN

class UniqueNumberGenerator;

class Entity
{
public:
   Entity( std::shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator );

   unsigned int GetUniqueId() const { return _uniqueId; }

   virtual sf::Vector2f GetPosition() const { return _position; }
   virtual void SetPosition( const sf::Vector2f& position ) { _position = position; }
   virtual void SetPositionX( float position ) { _position.x = position; }
   virtual void SetPositionY( float position ) { _position.y = position; }

   virtual sf::FloatRect GetHitBox() const { return _hitBox; }
   virtual void SetHitBox( const sf::FloatRect& hitBox ) { _hitBox = hitBox; }

   virtual sf::Vector2f GetVelocity() const { return _velocity; }
   virtual void SetVelocityX( float velocity ) { _velocity.x = velocity; }
   virtual void SetVelocityY( float velocity ) { _velocity.y = velocity; }

   virtual Direction GetDirection() const { return _direction; }
   virtual void SetDirection( Direction direction ) { _direction = direction; }

   virtual void MoveX( float distanceX );
   virtual void MoveY( float distanceY );

protected:
   unsigned int _uniqueId;
   sf::Vector2f _position;
   sf::FloatRect _hitBox;
   sf::Vector2f _velocity;
   Direction _direction;
};

NAMESPACE_END

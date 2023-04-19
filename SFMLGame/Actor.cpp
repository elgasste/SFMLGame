#include "Actor.h"

using namespace NAMESPACE;
using namespace sf;

Actor::Actor() :
   _position( Vector2f() ),
   _hitBox( FloatRect() ),
   _velocity( Vector2f() ),
   _direction( (Direction)0 )
{
}

void Actor::MoveX( float distanceX )
{
   _position.x += distanceX;
}

void Actor::MoveY( float distanceY )
{
   _position.y += distanceY;
}

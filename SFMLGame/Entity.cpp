#include "Entity.h"
#include "UniqueNumberGenerator.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

Entity::Entity( shared_ptr<UniqueNumberGenerator> uniqueNumberGenerator ) :
   _position( Vector2f() ),
   _hitBox( FloatRect() ),
   _velocity( Vector2f() ),
   _direction( (Direction)0 )
{
   _uniqueId = uniqueNumberGenerator->Generate();
}

void Entity::MoveX( float distanceX )
{
   _position.x += distanceX;
}

void Entity::MoveY( float distanceY )
{
   _position.y += distanceY;
}

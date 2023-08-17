#include "Entity.h"

using namespace NAMESPACE;

Entity::Entity() :
   _position( { 0, 0 } ),
   _angle( 0 ),
   _velocity( 0 )
{
}

void Entity::SetPosition( float x, float y )
{
   _position.x = x;
   _position.y = y;
}

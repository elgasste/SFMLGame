#include <math.h>

#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

Entity::Entity() :
   _position( Vector2f( 0, 0 ) ),
   _angle( 0 ),
   _forwardVelocity( 0 ),
   _sidewaysVelocity( 0 )
{
}

void Entity::SetPosition( float x, float y )
{
   _position.x = x;
   _position.y = y;
}

void Entity::SetAngle( float angle )
{
   _angle = angle;
   NORMALIZE_ANGLE( _angle );
}

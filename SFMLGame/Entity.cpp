#include <math.h>

#include "Entity.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

Entity::Entity() :
   _position( Vector2f( 0, 0 ) ),
   _hitBox( FloatRect( 0, 0, 0, 0 ) ),
   _angle( 0 ),
   _forwardVelocity( 0 ),
   _sidewaysVelocity( 0 ),
   _hitBoxCornerRayLength( 0 ),
   _hitBoxFrontCornerAngle( 0 ),
   _hitBoxRearCornerAngle( 0 )
{
}

void Entity::SetPosition( float x, float y )
{
   _position.x = x;
   _position.y = y;
}

// MUFFINS: do we even want to do collision detection this way? because a radius might be easier.
void Entity::SetHitBox( float x, float y, float width, float height )
{
   _hitBox.left = x;
   _hitBox.top = y;
   _hitBox.width = width;
   _hitBox.height = height;

   // distance from the center of the hit box to any corner
   _hitBoxCornerRayLength = sqrtf( powf( _hitBox.width / 2.0f, 2 ) + powf( _hitBox.height / 2.0f, 2 ) );

   // angle to hit box front corners (positive is left corner, negative is right corner)
   _hitBoxFrontCornerAngle = atan2f( _hitBox.width / 2.0f, _hitBox.height / 2.0f );
   NORMALIZE_ANGLE( _hitBoxFrontCornerAngle ); // this may not be necessary, but whatever

   // angle to hit box rear corners (positive is left corner, negative is right corner)
   _hitBoxRearCornerAngle = RAD_180 - _hitBoxFrontCornerAngle;
   NORMALIZE_ANGLE( _hitBoxRearCornerAngle );
}

void Entity::SetAngle( float angle )
{
   _angle = angle;
   NORMALIZE_ANGLE( _angle );
}

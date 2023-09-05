#include "Entity.h"

using namespace NAMESPACE;

Entity::Entity() :
   _hitBox( { 0, 0, 0, 0 } ),
   _position( { 0, 0 } ),
   _direction( (Direction)0 ),
   _velocity( 0 )
{
}

void Entity::SetHitBoxDimensions( float width, float height )
{
   _hitBox.width = width;
   _hitBox.height = height;
   _hitBox.left = _position.x - ( width / 2.0f );
   _hitBox.top = _position.y - ( height / 2.0f );
}

void Entity::SetPosition( float x, float y )
{
   _position.x = x;
   _position.y = y;

   _hitBox.left = x - ( _hitBox.width / 2.0f );
   _hitBox.top = y - ( _hitBox.height / 2.0f );
}

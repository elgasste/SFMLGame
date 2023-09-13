#include "Entity.h"

using namespace NAMESPACE;

Entity::Entity() :
   _position( { 0, 0 } ),
   _hitBoxSize( { 0, 0 } ),
   _hitBoxOffset( { 0, 0 } ),
   _direction( (Direction)0 ),
   _isMoving( false )
{
}

void Entity::SetPosition( float x, float y )
{
   _position.x = x;
   _position.y = y;
}

void Entity::SetHitBoxSize( float width, float height )
{
   _hitBoxSize.x = width;
   _hitBoxSize.y = height;
}

void Entity::SetHitBoxOffset( float x, float y )
{
   _hitBoxOffset.x = x;
   _hitBoxOffset.y = y;
}

#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

float Geometry::AngleToPoint( const sf::Vector2f& origin, const sf::Vector2f& point )
{
   return atan2f( origin.y - point.y, point.x - origin.x );
}

void Geometry::NormalizeAngle( float& angle )
{
   while ( angle >= RAD_360 )
   {
      angle -= RAD_360;
   }
   while ( angle < 0 )
   {
      angle += RAD_360;
   }
}

bool Geometry::IsPointOnRightSide( float pointX, float pointY, float p1x, float p1y, float p2x, float p2y )
{
   auto dx = p2x - p1x;
   auto dy = p2y - p1y;

   if ( dx == 0 )
   {
      // shortcut if linedef is vertical
      return ( dy > 0 ) ? pointX <= p1x : pointX > p1x;
   }
   else if ( dy == 0 )
   {
      // shortcut if linedef is horizontal
      return ( dx > 0 ) ? pointY > p1y : pointY <= p1y;
   }
   else
   {
      return CROSS_PRODUCT( p1x, p1y, pointX, pointY, dx, dy ) > 0;
   }
}

// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345
// Returns true if the lines intersect, and stores the intersection point in pIntersect
bool Geometry::LinesIntersect( float l1StartX, float l1StartY, float l1EndX, float l1EndY,
                               float l2StartX, float l2StartY, float l2EndX, float l2EndY,
                               Vector2f* pIntersect )
{
   auto pdx = l1EndX - l1StartX;
   auto pdy = l1EndY - l1StartY;
   auto ldx = l2EndX - l2StartX;
   auto ldy = l2EndY - l2StartY;
   auto cp = -ldx * pdy + pdx * ldy;

   if ( cp == 0.0f )
   {
      // lines are parallel or collinear
      return false;
   }

   auto s = ( -pdy * ( l1StartX - l2StartX ) + pdx * ( l1StartY - l2StartY ) ) / cp;
   auto t = ( ldx * ( l1StartY - l2StartY ) - ldy * ( l1StartX - l2StartX ) ) / cp;

   if ( s >= 0 && s <= 1 && t >= 0 && t <= 1 )
   {
      // collision detected
      if ( pIntersect != nullptr )
      {
         pIntersect->x = l1StartX + ( t * pdx );
         pIntersect->y = l1StartY + ( t * pdy );
      }

      return true;
   }

   return false;
}

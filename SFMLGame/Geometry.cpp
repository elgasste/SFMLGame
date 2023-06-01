#include <math.h>

#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

float Geometry::CrossProduct( float px, float py, float originX, float originY, float dx, float dy )
{
   return ( ( dx * ( py - originY ) ) - ( dy * ( px - originX ) ) );
}

bool Geometry::IsPointOnRightSide( float pointX, float pointY, float p1x, float p1y, float p2x, float p2y )
{
   auto dx = p2x - p1x;
   auto dy = p2y - p1y;

   // shortcut if linedef is vertical
   if ( dx == 0 )
   {
      return ( dy > 0 ) ? pointX <= p1x : pointX > p1x;
   }

   // shortcut if linedef is horizontal
   if ( dy == 0 )
   {
      return ( dx > 0 ) ? pointY > p1y : pointY <= p1y;
   }

   return Geometry::CrossProduct( pointX, pointY, p1x, p1y, dx, dy ) > 0;
}

// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345
// Returns true if the lines intersect, an stores the intersection point in pIntersect
bool Geometry::LineIntersectsLineseg( float p1x, float p1y, float p2x, float p2y, const Lineseg& lineseg, Vector2f& pIntersect )
{
   auto pdx = p2x - p1x;
   auto pdy = p2y - p1y;
   auto ldx = lineseg.end.x - lineseg.start.x;
   auto ldy = lineseg.end.y - lineseg.start.y;
   auto cp = -ldx * pdy + pdx * ldy;

   if ( cp == 0.0f )
   {
      // lines are parallel or collinear
      return false;
   }

   auto s = ( -pdy * ( p1x - lineseg.start.x ) + pdx * ( p1y - lineseg.start.y ) ) / cp;
   auto t = ( ldx * ( p1y - lineseg.start.y ) - ldy * ( p1x - lineseg.start.x ) ) / cp;

   if ( s >= 0 && s <= 1 && t >= 0 && t <= 1 )
   {
      // collision detected
      pIntersect.x = p1x + ( t * pdx );
      pIntersect.y = p1y + ( t * pdy );
      return true;
   }

   return false;
}

bool Geometry::RayIntersectsLineseg( const Vector2f& origin, float angle, const Lineseg& lineseg, Vector2f& pIntersect )
{
   auto dx = cosf( angle ) * RAY_LENGTH;
   auto dy = tanf( angle ) * dx;

   return LineIntersectsLineseg( origin.x, origin.y, origin.x + dx, origin.y - dy, lineseg, pIntersect );
}

bool Geometry::IsLinesegInView( const Vector2f& origin, float leftAngle, float rightAngle, const Lineseg& lineseg )
{
   auto dx = cosf( leftAngle ) * RAY_LENGTH;
   auto dy = tanf( leftAngle ) * dx;

   if ( IsPointOnRightSide( lineseg.start.x, lineseg.start.y, origin.x, origin.y, origin.x + dx, origin.y - dy ) )
   {
      dx = cosf( rightAngle ) * RAY_LENGTH;
      dy = tanf( rightAngle ) * dx;

      return !IsPointOnRightSide( lineseg.start.x, lineseg.start.y, origin.x, origin.y, origin.x + dx, origin.y - dy );
   }
   else
   {
      return IsPointOnRightSide( lineseg.end.x, lineseg.end.y, origin.x, origin.y, origin.x + dx, origin.y - dy );
   }
}

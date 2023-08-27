#include <math.h>

#include "Geometry.h"

using namespace NAMESPACE;
using namespace sf;

float Geometry::AngleToPoint( const sf::Vector2f& origin, const sf::Vector2f& point )
{
   return atan2f( origin.y - point.y, point.x - origin.x );
}

float Geometry::CrossProduct( float px, float py, float originX, float originY, float dx, float dy )
{
   return ( ( dx * ( py - originY ) ) - ( dy * ( px - originX ) ) );
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
      return Geometry::CrossProduct( pointX, pointY, p1x, p1y, dx, dy ) > 0;
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

bool Geometry::RayIntersectsLine( const Vector2f& origin,
                                  float angle,
                                  float lStartX,
                                  float lStartY,
                                  float lEndX,
                                  float lEndY,
                                  Vector2f* pIntersect )
{
   auto dx = cosf( angle ) * RAY_LENGTH;
   auto dy = tanf( angle ) * dx;

   return LinesIntersect( origin.x, origin.y, origin.x + dx, origin.y - dy, lStartX, lStartY, lEndX, lEndY, pIntersect );
}

bool Geometry::IsLineInView( const Vector2f& origin,
                             float leftViewAngle, float rightViewAngle,
                             float lStartX, float lStartY, float lEndX, float lEndY,
                             bool& isLineStartInView,
                             bool& isLineEndInView,
                             bool useBackfaceCulling )
{
   if ( RayIntersectsLine( origin, leftViewAngle, lStartX, lStartY, lEndX, lEndY, nullptr ) )
   {
      auto dxRight = cosf( rightViewAngle ) * RAY_LENGTH;
      auto dyRight = tanf( rightViewAngle ) * dxRight;
      isLineEndInView = !IsPointOnRightSide( lEndX, lEndY, origin.x, origin.y, origin.x + dxRight, origin.y - dyRight );

      if ( useBackfaceCulling )
      {
         isLineStartInView = false;
      }
      else
      {
         auto dxLeft = cosf( leftViewAngle ) * RAY_LENGTH;
         auto dyLeft = tanf( leftViewAngle ) * dxLeft;
         isLineStartInView = IsPointOnRightSide( lStartX, lStartY, origin.x, origin.y, origin.x + dxLeft, origin.y - dyLeft );
      }

      return true;
   }
   else if ( RayIntersectsLine( origin, rightViewAngle, lStartX, lStartY, lEndX, lEndY, nullptr ) )
   {
      auto dxLeft = cosf( leftViewAngle ) * RAY_LENGTH;
      auto dyLeft = tanf( leftViewAngle ) * dxLeft;
      isLineStartInView = IsPointOnRightSide( lStartX, lStartY, origin.x, origin.y, origin.x + dxLeft, origin.y - dyLeft );

      if ( useBackfaceCulling )
      {
         isLineEndInView = false;
      }
      else
      {
         auto dxRight = cosf( rightViewAngle ) * RAY_LENGTH;
         auto dyRight = tanf( rightViewAngle ) * dxRight;
         isLineEndInView = !IsPointOnRightSide( lStartX, lStartY, origin.x, origin.y, origin.x + dxRight, origin.y - dyRight );
      }

      return true;
   }
   else
   {
      auto dxLeft = cosf( leftViewAngle ) * RAY_LENGTH;
      auto dyLeft = tanf( leftViewAngle ) * dxLeft;
      isLineStartInView = IsPointOnRightSide( lStartX, lStartY, origin.x, origin.y, origin.x + dxLeft, origin.y - dyLeft );

      auto dxRight = cosf( rightViewAngle ) * RAY_LENGTH;
      auto dyRight = tanf( rightViewAngle ) * dxRight;
      isLineEndInView = !IsPointOnRightSide( lStartX, lStartY, origin.x, origin.y, origin.x + dxRight, origin.y - dyRight );

      return isLineStartInView && isLineEndInView;
   }
}

float Geometry::Raycast( const sf::Vector2f& origin, const sf::Vector2f& point, float playerAngle, float rayAngle )
{
   // this is from the Wolfenstein 3D book. it's supposed to fix fish-eye, but sometimes it seems to cause reverse-fish-eye?
   //return ( ( point.x - origin.x ) * cosf( playerAngle ) ) - ( ( point.y - origin.y ) * sinf( playerAngle ) );

   // I can't really tell if this method works better (it's from a YouTube video), it might even do the same thing.
   auto rayDistance = sqrtf( powf( point.x - origin.x, 2 ) + powf( point.y - origin.y, 2 ) );
   auto angleDelta = playerAngle - rayAngle;
   NORMALIZE_ANGLE( angleDelta );
   return rayDistance * cosf( angleDelta );
}

#pragma once

#include "Common.h"

#define RAD_45       0.785398185f
#define RAD_90       1.57079637f
#define RAD_135      2.356194555f
#define RAD_180      3.14159274f
#define RAD_225      3.926990925f
#define RAD_270      4.71238899f
#define RAD_315      5.497787295f
#define RAD_360      6.28318548f

#define CROSS_PRODUCT( x1, y1, x2, y2, dx, dy ) ( ( dx * ( y2 - y1 ) ) - ( dy * ( x2 - x1 ) ) )

NAMESPACE_BEGIN

class Geometry
{
public:
   static void NormalizeAngle( float& angle );
   static float AngleToPoint( const sf::Vector2f& origin, const sf::Vector2f& point );
   static bool IsPointOnRightSide( float pointX, float pointY, float p1x, float p1y, float p2x, float p2y );
   static bool LinesIntersect( float l1StartX, float l1StartY, float l1EndX, float l1EndY,
                               float l2StartX, float l2StartY, float l2EndX, float l2EndY,
                               sf::Vector2f* pIntersect );
};

NAMESPACE_END

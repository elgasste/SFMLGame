#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"

#define PI           3.14159274f
#define RAD_30       0.523598790f
#define RAD_45       0.785398185f
#define RAD_90       1.57079637f
#define RAD_180      PI
#define RAD_270      4.71238899f
#define RAD_360      6.28318548f

#define RAY_LENGTH   1'000'000.0f;

#define NORMALIZE_ANGLE( x ) while ( x >= RAD_360 ) x -= RAD_360; while ( x < 0 ) x += RAD_360;

NAMESPACE_BEGIN

class Geometry
{
public:
   static float AngleToPoint( const sf::Vector2f& origin, const sf::Vector2f& point );
   static float CrossProduct( float px, float py, float originX, float originY, float dx, float dy );
   static bool IsPointOnRightSide( float pointX, float pointY, float p1x, float p1y, float p2x, float p2y );
   static bool LinesIntersect( float l1StartX, float l1StartY, float l1EndX, float l1EndY,
                               float l2StartX, float l2StartY, float l2EndX, float l2EndY,
                               sf::Vector2f* pIntersect );
   static bool RayIntersectsLine( const sf::Vector2f& origin,
                                  float angle,
                                  float lStartX, float lStartY, float lEndX, float lEndY,
                                  sf::Vector2f* pIntersect );
   static bool IsLineInView( const sf::Vector2f& origin,
                             float leftViewAngle, float rightViewAngle,
                             float lStartX, float lStartY, float lEndX, float lEndY,
                             bool& isLineStartInView,
                             bool& isLineEndInView,
                             bool useBackfaceCulling );
   static float Raycast( const sf::Vector2f& origin, const sf::Vector2f& point, float playerAngle, float rayAngle );
};

NAMESPACE_END

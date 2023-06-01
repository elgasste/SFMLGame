#pragma once

#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "Lineseg.h"

#define RAD_30       0.523598790f
#define RAD_360      6.28318548f

#define RAY_LENGTH   1'000'000.0f;

NAMESPACE_BEGIN

class Geometry
{
public:
   static float CrossProduct( float px, float py, float originX, float originY, float dx, float dy );
   static bool IsPointOnRightSide( float pointX, float pointY, float p1x, float p1y, float p2x, float p2y );
   static bool LineIntersectsLineseg( float p1x, float p1y, float p2x, float p2y, const Lineseg& lineseg, sf::Vector2f& pIntersect );
   static bool RayIntersectsLineseg( const sf::Vector2f& origin, float angle, const Lineseg& lineseg, sf::Vector2f& pIntersect );
   static bool IsLinesegInView( const sf::Vector2f& origin, float leftAngle, float rightAngle, const Lineseg& lineseg );
};

NAMESPACE_END

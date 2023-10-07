#pragma once

#include "Common.h"
#include "KeyCode.h"
#include "Button.h"
#include "Direction.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   std::map<sf::Keyboard::Key, Button> KeyBindingsMap;

   bool ShowDiagnostics;

   int HitBoxBlockSize;
   float LinesegClipDistance;

   sf::Vector2f DefaultPlayerPosition;
   Direction DefaultPlayerDirection;
   float PlayerHitBoxWidth;
   float PlayerHitBoxHeight;
   float PlayerVelocityIncrement;
   float PlayerVelocityDiagonalScalar;

   bool ShowWireframeMap;
};

NAMESPACE_END

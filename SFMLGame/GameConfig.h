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
   std::map<KeyCode, Button> KeyBindingsMap;

   bool ShowDiagnostics;

   int HitBoxBlockSize;
   float LinesegClipDistance;

   sf::Vector2f DefaultPlayerPosition;
   Direction DefaultPlayerDirection;
   float MaximumPlayerVelocity;
   float PlayerHitBoxWidth;
   float PlayerHitBoxHeight;
   float PlayerVelocityIncrement;
};

NAMESPACE_END

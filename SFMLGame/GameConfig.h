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

   sf::Vector2f DefaultPlayerPosition;
   Direction DefaultPlayerDirection;
   float MaximumPlayerVelocity;
   int PlayerHitBoxWidth;
   int PlayerHitBoxHeight;
   float PlayerVelocityIncrement;
};

NAMESPACE_END

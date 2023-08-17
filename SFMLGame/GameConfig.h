#pragma once

#include "Common.h"
#include "KeyCode.h"
#include "Button.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   std::map<KeyCode, Button> KeyBindingsMap;

   bool ShowDiagnostics;

   sf::Vector2f DefaultBallPosition;
   float DefaultBallAngle;
   float DefaultBallVelocity;
   float BallDiameter;
};

NAMESPACE_END

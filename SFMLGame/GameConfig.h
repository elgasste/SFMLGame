#pragma once

#include "Common.h"
#include "Button.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   std::map<sf::Keyboard::Key, Button> KeyBindingsMap;

   bool ShowDiagnostics;

   sf::Vector2f DefaultBallPosition;
   float DefaultBallAngle;
   float DefaultBallVelocity;
   float MinimumBallVelocity;
   float MaximumBallVelocity;
   float BallDiameter;

   float BallTurnAngleIncrement;
   float BallVelocityIncrement;
};

NAMESPACE_END

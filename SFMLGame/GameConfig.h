#pragma once

#include <string>
#include <map>
#include <SFML/System/Vector2.hpp>

#include "Common.h"
#include "KeyCode.h"
#include "Button.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   int ScreenWidth;
   int ScreenHeight;

   std::string WindowTitle;
   unsigned int WindowStyle;

   std::map<KeyCode, Button> KeyBindingsMap;

   sf::Vector2f DefaultPlayerPosition;
   float DefaultPlayerRadius;
   float DefaultPlayerAngle;

   float MaxPlayerVelocity;
   float PlayerVelocityAcceleration;
   float PlayerVelocityDeceleration;

   float MouseMoveAngleIncrement;
   float KeyboardTurnAngleIncrement;
   float KeyboardMoveIncrement;
};

NAMESPACE_END

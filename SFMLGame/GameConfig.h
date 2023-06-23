#pragma once

#include <string>
#include <map>

#include <SFML/Graphics/Color.hpp>

#include "Common.h"
#include "KeyCode.h"
#include "Button.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   long long MinimumFrameRate;
   long long MaximumFrameRate;

   int ScreenWidth;
   int ScreenHeight;

   std::string WindowTitle;
   unsigned int WindowStyle;

   std::map<KeyCode, Button> KeyBindingsMap;

   bool ShowDiagnostics;

   float DiagnosticsXPosition;
   float DiagnosticsYPosition;
   float DiagnosticsWidth;
   float DiagnosticsHeight;
   float DiagnosticsTextMargin;
   std::string DiagnosticsFont;
   unsigned int DiagnosticsCharSize;
   sf::Color DiagnosticsTextColor;
   sf::Color DiagnosticsBackgroundColor;

   std::string MenuFont;
   unsigned int MenuCharSize;
   sf::Color MenuTextColor;
   float MenuCaratOffset;
   float MenuCaratBlinkRate;
};

NAMESPACE_END

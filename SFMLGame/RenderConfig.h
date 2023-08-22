#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig
{
public:
   RenderConfig();

public:
   long long MinimumFrameRate;
   long long MaximumFrameRate;

   int ScreenWidth;
   int ScreenHeight;

   std::string WindowTitle;
   unsigned int WindowStyle;

   float DiagnosticsXPosition;
   float DiagnosticsYPosition;
   float DiagnosticsWidth;
   float DiagnosticsHeight;
   float DiagnosticsTextMargin;
   std::string DiagnosticsFont;
   unsigned int DiagnosticsCharSize;
   sf::Color DiagnosticsTextColor;
   sf::Color DiagnosticsBackgroundColor;

   sf::Color ArenaBackgroundColor;

   std::string MessageFont;
   unsigned int MessageCharSize;
   sf::Color MessageTextColor;

   std::string MainMenuFont;
   unsigned int MainMenuCharSize;
   sf::Color MainMenuTextColor;
   float MainMenuCaratOffset;
   float MainMenuCaratBlinkRate;

   sf::Vector2f BallOrigin;
};

NAMESPACE_END

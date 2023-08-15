#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

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

   std::string MessageFont;
   unsigned int MessageCharSize;
   sf::Color MessageTextColor;

   std::string MenuFont;
   unsigned int MenuCharSize;
   sf::Color MenuTextColor;
   float MenuCaratOffset;
   float MenuCaratBlinkRate;
};

NAMESPACE_END

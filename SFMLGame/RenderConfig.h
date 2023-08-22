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

   std::string TitleMessageFont;
   unsigned int TitleMessageCharSize;
   sf::Color TitleMessageTextColor;

   std::string TitleMenuFont;
   unsigned int TitleMenuCharSize;
   sf::Color TitleMenuTextColor;

   std::string PlayingMessageFont;
   unsigned int PlayingMessageCharSize;
   sf::Color PlayingMessageTextColor;

   std::string MainMenuFont;
   unsigned int MainMenuCharSize;
   sf::Color MainMenuTextColor;
   float MainMenuCaratOffset;
   float MainMenuCaratBlinkRate;

   sf::Vector2f BallOrigin;
};

NAMESPACE_END

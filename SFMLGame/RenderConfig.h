#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderConfig
{
public:
   RenderConfig();

public:
   unsigned int MinimumFrameRate;
   unsigned int MaximumFrameRate;

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
   float DiagnosticsCurrentFrameRateRefreshSeconds;

   sf::Color ArenaBackgroundColor;

   sf::Color TitleMenuBackgroundColor;
   std::string TitleMessageFont;
   unsigned int TitleMessageCharSize;
   sf::Color TitleMessageTextColor;
   float TitleMenuCaratOffset;
   float TitleMenuCaratBlinkRate;

   std::string TitleMenuFont;
   unsigned int TitleMenuCharSize;
   sf::Color TitleMenuTextColor;

   std::string PlayingMessageFont;
   unsigned int PlayingMessageCharSize;
   sf::Color PlayingMessageTextColor;

   sf::Color MainMenuBackgroundColor;
   std::string MainMenuFont;
   unsigned int MainMenuCharSize;
   sf::Color MainMenuTextColor;
   float MainMenuCaratOffset;
   float MainMenuCaratBlinkRate;
   sf::Color MainMenuBallDimmer;

   sf::Vector2f BallOrigin;
};

NAMESPACE_END

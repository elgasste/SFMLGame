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

   sf::Color TitleMenuBackgroundColor;
   std::string TitleMessageFont;
   unsigned int TitleMessageCharSize;
   sf::Color TitleMessageTextColor;
   float TitleMenuCaratOffset;
   float TitleMenuCaratBlinkRate;

   std::string TitleMenuFont;
   unsigned int TitleMenuCharSize;
   sf::Color TitleMenuTextColor;

   sf::Color MainMenuBackgroundColor;
   std::string MainMenuFont;
   unsigned int MainMenuCharSize;
   sf::Color MainMenuTextColor;
   float MainMenuCaratOffset;
   float MainMenuCaratBlinkRate;
   sf::Color MainMenuBackdropDimmer;

   float SpriteScalar;

   sf::Vector2i PlayerSpriteSize;
   sf::Vector2f PlayerSpriteOrigin;
   int PlayerSpriteMovementFrames;
   float PlayerSpriteFrameIncrement;
};

NAMESPACE_END

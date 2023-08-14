#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class GameConfig;

class RenderConfig
{
public:
   RenderConfig( std::shared_ptr<GameConfig> gameConfig );

public:
   long long MinimumFrameRate;
   long long MaximumFrameRate;

   float FovAngle;
   float FovAngleIncrement;

   float WallHeight;
   float ProjectionPlaneDelta;
   float LightingScalar;
   int LightingMinimum;
   float SpriteOffsetScalar;
   int SkySpriteId;

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

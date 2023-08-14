#include "RenderConfig.h"
#include "GameConfig.h"
#include "Geometry.h"

using namespace NAMESPACE;
using namespace std;

RenderConfig::RenderConfig( shared_ptr<GameConfig> gameConfig )
{
   MinimumFrameRate = 30;
   MaximumFrameRate = 120;

   FovAngle = RAD_30 * 2.0f;
   FovAngleIncrement = FovAngle / gameConfig->ScreenWidth;

   WallHeight = 100.0f;
   ProjectionPlaneDelta = gameConfig->ScreenHeight / 1.5f;
   LightingScalar = 1.3f;
   LightingMinimum = 25;
   SpriteOffsetScalar = 25.0f;

   ShowDiagnostics = false;

   DiagnosticsWidth = 450;
   DiagnosticsHeight = 180;
   DiagnosticsXPosition = gameConfig->ScreenWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 20;
   DiagnosticsFont = "consolas.ttf";
   DiagnosticsCharSize = 24;
   DiagnosticsTextColor = sf::Color::White;
   DiagnosticsBackgroundColor = sf::Color::Blue;

   MessageFont = "consolas.ttf";
   MessageCharSize = 32;
   MessageTextColor = sf::Color::White;

   MenuFont = "consolas.ttf";
   MenuCharSize = 32;
   MenuTextColor = sf::Color::White;
   MenuCaratOffset = 20;
   MenuCaratBlinkRate = 0.2f;
}

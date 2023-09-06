#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderConfig::RenderConfig()
{
   MinimumFrameRate = 30;
   MaximumFrameRate = 120;

   ScreenWidth = 1920;
   ScreenHeight = 1080;

   WindowTitle = IDS_WindowTitle;
   WindowStyle = Style::Titlebar | Style::Close;

   DiagnosticsWidth = 450;
   DiagnosticsHeight = 265;
   DiagnosticsXPosition = ScreenWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 20;
   DiagnosticsFont = "Resources/Fonts/Consolas.ttf";
   DiagnosticsCharSize = 24;
   DiagnosticsTextColor = Color::White;
   DiagnosticsBackgroundColor = Color::Blue;

   ArenaBackgroundColor = Color( 48, 48, 48 );

   TitleMenuBackgroundColor = Color::Black;
   TitleMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   TitleMenuCharSize = 128;
   TitleMenuTextColor = Color( 200, 200, 255 );
   TitleMenuCaratOffset = 40;
   TitleMenuCaratBlinkRate = 0.25f;

   MainMenuBackgroundColor = Color( 48, 48, 48, 128 );
   MainMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   MainMenuCharSize = 96;
   MainMenuTextColor = Color( 200, 200, 255 );
   MainMenuCaratOffset = 30;
   MainMenuCaratBlinkRate = 0.25f;
   MainMenuBackdropDimmer = Color( 128, 128, 128 );

   SpriteScalar = 2.5f;

   PlayerSpriteSize = { 64, 64 };
   PlayerSpriteOrigin = { 32, 37 };
   PlayerSpriteMovementFrames = 9;
   PlayerSpriteFrameIncrement = 0.05f;
}

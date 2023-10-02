#include "RenderConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

RenderConfig::RenderConfig()
{
   MinimumFrameRate = 10;
   MaximumFrameRate = 12000;

   ScreenWidth = 1920;
   ScreenHeight = 1280;
   ViewWidth = 960;
   ViewHeight = 640;

   WindowTitle = IDS_WindowTitle;
   WindowStyle = Style::Titlebar | Style::Close;

   DiagnosticsWidth = 225;
   DiagnosticsHeight = 93;
   DiagnosticsXPosition = ViewWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 10;
   DiagnosticsFont = "Resources/Fonts/Consolas.ttf";
   DiagnosticsCharSize = 12;
   DiagnosticsTextColor = Color::White;
   DiagnosticsBackgroundColor = Color::Blue;

   ArenaBackgroundColor = Color::Black;

   TitleMenuBackgroundColor = Color::Black;
   TitleMenuFont = "Resources/Fonts/Goudy Mediaeval Regular.ttf";
   TitleMenuCharSize = 48;
   TitleMenuTextColor = Color( 200, 200, 255 );
   TitleMenuCaratOffset = 15;
   TitleMenuCaratBlinkRate = 0.25f;

   MainMenuBackgroundColor = Color::Black;
   MainMenuFont = "Resources/Fonts/Goudy Mediaeval Regular.ttf";
   MainMenuCharSize = 48;
   MainMenuTextColor = Color( 200, 200, 255 );
   MainMenuCaratOffset = 15;
   MainMenuCaratBlinkRate = 0.25f;
   MainMenuBackdropDimmer = Color( 128, 128, 128 );

   PlayerSpriteSize = { 64, 64 };
   PlayerSpriteOrigin = { 32, 38 };
   PlayerSpriteMovementFrames = 8;
   PlayerSpriteFrameIncrement = 0.05f;

   WireframeLinedefColor = Color::White;
   WireframePlayerHitBoxFillColor = Color::Magenta;
}

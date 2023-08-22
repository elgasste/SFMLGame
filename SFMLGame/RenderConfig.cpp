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

   ArenaBackgroundColor = Color( 64, 64, 64 );

   MessageFont = "Resources/Fonts/Consolas.ttf";
   MessageCharSize = 32;
   MessageTextColor = Color::White;

   MainMenuFont = "Resources/Fonts/Consolas.ttf";
   MainMenuCharSize = 32;
   MainMenuTextColor = Color::White;
   MainMenuCaratOffset = 20;
   MainMenuCaratBlinkRate = 0.2f;

   BallOrigin = { 290.5f, 290.5f };
}

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
   DiagnosticsHeight = 320;
   DiagnosticsXPosition = ScreenWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 20;
   DiagnosticsFont = "Resources/Fonts/Consolas.ttf";
   DiagnosticsCharSize = 24;
   DiagnosticsTextColor = Color::White;
   DiagnosticsBackgroundColor = Color::Blue;
   DiagnosticsCurrentFrameRateRefreshSeconds = 1.0f;

   ArenaBackgroundColor = Color( 48, 48, 48 );

   TitleMenuBackgroundColor = Color::Black;
   TitleMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   TitleMenuCharSize = 128;
   TitleMenuTextColor = Color( 200, 200, 255 );
   TitleMenuCaratOffset = 40;
   TitleMenuCaratBlinkRate = 0.25f;

   PlayingMessageFont = "Resources/Fonts/Rubber-Duck.ttf";
   PlayingMessageCharSize = 32;
   PlayingMessageTextColor = Color( 200, 200, 255 );

   MainMenuBackgroundColor = Color( 48, 48, 48, 128 );
   MainMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   MainMenuCharSize = 96;
   MainMenuTextColor = Color( 200, 200, 255 );
   MainMenuCaratOffset = 30;
   MainMenuCaratBlinkRate = 0.25f;
   MainMenuBallDimmer = Color( 128, 128, 128 );

   BallOrigin = { 290.5f, 290.5f };
}

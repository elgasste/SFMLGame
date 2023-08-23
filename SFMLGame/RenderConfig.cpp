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

   TitleMessageFont = "Resources/Fonts/Rubber-Duck.ttf";
   TitleMessageCharSize = 32;
   TitleMessageTextColor = Color::White;

   TitleMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   TitleMenuCharSize = 96;
   TitleMenuTextColor = Color::White;

   PlayingMessageFont = "Resources/Fonts/Rubber-Duck.ttf";
   PlayingMessageCharSize = 32;
   PlayingMessageTextColor = Color::White;

   MainMenuFont = "Resources/Fonts/Rubber-Duck.ttf";
   MainMenuCharSize = 96;
   MainMenuTextColor = Color::White;
   MainMenuCaratOffset = 20;
   MainMenuCaratBlinkRate = 0.25f;

   BallOrigin = { 290.5f, 290.5f };
}

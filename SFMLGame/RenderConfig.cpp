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
   DiagnosticsHeight = 180;
   DiagnosticsXPosition = ScreenWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 20;
   DiagnosticsFont = "Resources/Fonts/Consolas.ttf";
   DiagnosticsCharSize = 24;
   DiagnosticsTextColor = Color::White;
   DiagnosticsBackgroundColor = Color::Blue;

   MessageFont = "Resources/Fonts/Consolas.ttf";
   MessageCharSize = 32;
   MessageTextColor = Color::White;

   MenuFont = "Resources/Fonts/Consolas.ttf";
   MenuCharSize = 32;
   MenuTextColor = Color::White;
   MenuCaratOffset = 20;
   MenuCaratBlinkRate = 0.2f;
}

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

   WindowTitle = "SFML Game";
   WindowStyle = Style::Titlebar | Style::Close;

   DiagnosticsWidth = 450;
   DiagnosticsHeight = 180;
   DiagnosticsXPosition = ScreenWidth - DiagnosticsWidth;
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

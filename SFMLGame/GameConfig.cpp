#include <SFML/Window/WindowStyle.hpp>

#include "GameConfig.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

GameConfig::GameConfig()
{
   MinimumFrameRate = 30;
   MaximumFrameRate = 120;

   ScreenWidth = 1920;
   ScreenHeight = 1080;

   WindowTitle = "SFML Game";
   WindowStyle = Style::Titlebar | Style::Close;

   KeyBindingsMap =
   {
      { KeyCode::Escape, Button::Back },
      { KeyCode::F12, Button::Diagnostics }
   };

   ShowDiagnostics = false;

   DiagnosticsWidth = 450;
   DiagnosticsHeight = 180;
   DiagnosticsXPosition = ScreenWidth - DiagnosticsWidth;
   DiagnosticsYPosition = 0;
   DiagnosticsTextMargin = 20;
   DiagnosticsFont = "consolas.ttf";
   DiagnosticsCharSize = 24;
   DiagnosticsTextColor = sf::Color::White;
   DiagnosticsBackgroundColor = sf::Color::Blue;
}

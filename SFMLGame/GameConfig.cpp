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
      { KeyCode::Return, Button::Action },
      { KeyCode::Left, Button::Left },
      { KeyCode::Up, Button::Up },
      { KeyCode::Right, Button::Right },
      { KeyCode::Down, Button::Down },
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

   MessageFont = "consolas.ttf";
   MessageCharSize = 32;
   MessageTextColor = sf::Color::White;

   MenuFont = "consolas.ttf";
   MenuCharSize = 32;
   MenuTextColor = sf::Color::White;
   MenuCaratOffset = 20;
   MenuCaratBlinkRate = 0.2f;
}

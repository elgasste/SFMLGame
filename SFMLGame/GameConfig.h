#pragma once

#include <string>
#include <map>

#include "Common.h"
#include "KeyCode.h"
#include "Button.h"

NAMESPACE_BEGIN

class GameConfig
{
public:
   GameConfig();

public:
   int ScreenWidth;
   int ScreenHeight;

   std::string WindowTitle;
   unsigned int WindowStyle;

   std::map<KeyCode, Button> KeyBindingsMap;
};

NAMESPACE_END

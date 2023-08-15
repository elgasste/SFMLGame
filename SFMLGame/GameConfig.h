#pragma once

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
   std::map<KeyCode, Button> KeyBindingsMap;

   bool ShowDiagnostics;
};

NAMESPACE_END

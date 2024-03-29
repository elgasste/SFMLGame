#pragma once

#include "Common.h"
#include "Menu.h"

NAMESPACE_BEGIN

class EventQueue;

class MainMenu : public Menu
{
public:
   MainMenu( std::shared_ptr<EventQueue> eventQueue );
};

NAMESPACE_END

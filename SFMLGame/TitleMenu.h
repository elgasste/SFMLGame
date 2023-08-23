#pragma once

#include "Common.h"
#include "Menu.h"

NAMESPACE_BEGIN

class EventQueue;

class TitleMenu : public Menu
{
public:
   TitleMenu( std::shared_ptr<EventQueue> eventQueue );
};

NAMESPACE_END

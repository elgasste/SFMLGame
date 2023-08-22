#pragma once

#include "Common.h"
#include "MenuOption.h"

NAMESPACE_BEGIN

class EventQueue;

class Menu
{
public:
   Menu( std::shared_ptr<EventQueue> eventQueue );

   virtual int GetOptionCount() const { return (int)_options.size(); }
   virtual const MenuOption& GetOptionByIndex( int index ) const { return _options.at( index ); }
   virtual int GetCurrentOptionIndex() const { return _currentOptionIndex; }
   virtual void ScrollUp();
   virtual void ScrollDown();
   virtual void SelectCurrentOption() const;

protected:
   std::shared_ptr<EventQueue> _eventQueue;

   std::vector<MenuOption> _options;
   int _currentOptionIndex;
};

NAMESPACE_END

#pragma once

#include "Common.h"
#include "MenuOption.h"

NAMESPACE_BEGIN

class EventQueue;

class PlayingStateMenu
{
public:
   PlayingStateMenu( std::shared_ptr<EventQueue> eventQueue );

   int GetOptionCount() const { return (int)_options.size(); }
   const MenuOption& GetOptionByIndex( int index ) const { return _options.at( index ); }
   int GetCurrentOptionIndex() const { return _currentOptionIndex; }
   void ScrollUp();
   void ScrollDown();
   void SelectCurrentOption() const;

private:
   std::shared_ptr<EventQueue> _eventQueue;

   std::vector<MenuOption> _options;
   int _currentOptionIndex;
};

NAMESPACE_END

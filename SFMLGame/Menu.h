#pragma once

#include <vector>

#include "Common.h"

NAMESPACE_BEGIN

class IMenuOption;

class Menu
{
public:
   Menu();

   void AddOption( std::shared_ptr<IMenuOption> option );
   int GetOptionCount() const { return (int)_options.size(); }
   std::shared_ptr<IMenuOption> GetOptionByIndex( int index ) const { return _options[index]; }
   int GetCurrentOptionIndex() const { return _currentOptionIndex; }
   void ScrollUp();
   void ScrollDown();
   void SelectCurrentOption() const;

private:
   std::vector<std::shared_ptr<IMenuOption>> _options;
   int _currentOptionIndex;
};

NAMESPACE_END

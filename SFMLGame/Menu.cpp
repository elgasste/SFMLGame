#include "Menu.h"
#include "IMenuOption.h"

using namespace NAMESPACE;
using namespace std;

Menu::Menu() :
   _currentOptionIndex( 0 )
{
}

void Menu::AddOption( shared_ptr<IMenuOption> option )
{
   _options.push_back( option );
}

void Menu::ScrollUp()
{
   _currentOptionIndex--;

   if ( _currentOptionIndex < 0 )
   {
      _currentOptionIndex = (int)_options.size() - 1;
   }
}

void Menu::ScrollDown()
{
   _currentOptionIndex++;

   if ( _currentOptionIndex >= (int)_options.size() )
   {
      _currentOptionIndex = 0;
   }
}

void Menu::SelectCurrentOption() const
{
   _options[_currentOptionIndex]->Select();
}

#include <SFML/Graphics.hpp>

#include "SFMLWindow.h"
#include "GameConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "GameEvent.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

SFMLWindow::SFMLWindow( shared_ptr<GameConfig> config,
                        shared_ptr<EventAggregator> eventAggregator,
                        shared_ptr<GameClock> clock ) :
   _config( config ),
   _eventAggregator( eventAggregator ),
   _clock( clock )
{
}

void SFMLWindow::Initialize()
{
   auto videoMode = VideoMode( _config->ScreenWidth, _config->ScreenHeight );
   _window = shared_ptr<RenderWindow>( new RenderWindow( videoMode, _config->WindowTitle, _config->WindowStyle ) );
}

void SFMLWindow::Show() const
{
   _window->clear();
   _window->display();
}

void SFMLWindow::HandleEvents() const
{
   static Event e;

   while ( _window->pollEvent( e ) )
   {
      switch ( e.type )
      {
         case Event::Closed:
            _window->close();
            _eventAggregator->RaiseEvent( GameEvent::Quit );
            break;
      }
   }
}

void SFMLWindow::Clear() const
{
   _window->clear();
}

void SFMLWindow::Draw( shared_ptr<sf::Drawable> drawable ) const
{
   _window->draw( *drawable );
}

void SFMLWindow::Render() const
{
   _window->display();
}

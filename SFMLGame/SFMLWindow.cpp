#include "SFMLWindow.h"
#include "RenderConfig.h"
#include "EventAggregator.h"
#include "GameClock.h"
#include "GameEvent.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

SFMLWindow::SFMLWindow( shared_ptr<RenderConfig> renderConfig,
                        shared_ptr<EventAggregator> eventAggregator,
                        shared_ptr<GameClock> clock ) :
   _renderConfig( renderConfig ),
   _eventAggregator( eventAggregator ),
   _clock( clock )
{
}

void SFMLWindow::Initialize()
{
   auto videoMode = VideoMode( _renderConfig->ScreenWidth, _renderConfig->ScreenHeight );
   _window = shared_ptr<RenderWindow>( new RenderWindow( videoMode, _renderConfig->WindowTitle, _renderConfig->WindowStyle ) );
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

void SFMLWindow::Draw( shared_ptr<Drawable> drawable ) const
{
   _window->draw( *drawable );
}

void SFMLWindow::Render() const
{
   _window->display();
}

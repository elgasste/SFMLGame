#include "SFMLWindow.h"
#include "RenderConfig.h"
#include "GameClock.h"
#include "InputStateController.h"
#include "GameEventType.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

SFMLWindow::SFMLWindow( shared_ptr<RenderConfig> renderConfig,
                        shared_ptr<GameClock> clock,
                        shared_ptr<InputStateController> inputStateController ) :
   _renderConfig( renderConfig ),
   _clock( clock ),
   _inputStateController( inputStateController )
{
}

void SFMLWindow::Initialize()
{
   auto videoMode = VideoMode( _renderConfig->ScreenWidth, _renderConfig->ScreenHeight );
   auto view = View( { 0, 0, _renderConfig->ViewWidth, _renderConfig->ViewHeight } );
   _window = shared_ptr<RenderWindow>( new RenderWindow( videoMode, _renderConfig->WindowTitle, _renderConfig->WindowStyle ) );
   _window->setView( view );

   _window->setKeyRepeatEnabled( false );
}

void SFMLWindow::Show() const
{
   _window->clear();
   _window->display();
}

void SFMLWindow::HandleEvents() const
{
   _inputStateController->UpdateKeyStates();
   _inputStateController->ReadMouseInput();

   static Event e;

   while ( _window->pollEvent( e ) )
   {
      switch ( e.type )
      {
         case Event::Closed:
            _window->close();
            break;
         case Event::KeyPressed:
            _inputStateController->KeyPressed( e.key.code );
            break;
         case Event::KeyReleased:
            _inputStateController->KeyReleased( e.key.code );
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

void SFMLWindow::Draw( const Drawable& drawable ) const
{
   _window->draw( drawable );
}

void SFMLWindow::Render() const
{
   _window->display();
}

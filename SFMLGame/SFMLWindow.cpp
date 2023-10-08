#include "SFMLWindow.h"
#include "RenderConfig.h"
#include "GameClock.h"
#include "InputReader.h"
#include "GameInputHandler.h"
#include "GameEventType.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

SFMLWindow::SFMLWindow( shared_ptr<RenderConfig> renderConfig,
                        shared_ptr<GameClock> clock,
                        shared_ptr<InputReader> inputReader,
                        shared_ptr<GameInputHandler> inputHandler ) :
   _renderConfig( renderConfig ),
   _clock( clock ),
   _inputReader( inputReader ),
   _inputHandler( inputHandler )
{
}

void SFMLWindow::Initialize()
{
   auto videoMode = VideoMode( _renderConfig->ScreenWidth, _renderConfig->ScreenHeight );
   _window = shared_ptr<RenderWindow>( new RenderWindow( videoMode, _renderConfig->WindowTitle, _renderConfig->WindowStyle ) );

   _window->setKeyRepeatEnabled( false );
}

void SFMLWindow::Show() const
{
   _window->clear();
   _window->display();
}

void SFMLWindow::HandleEvents() const
{
   _inputReader->UpdateKeyStates();
   _inputReader->ReadMouseInput();

   static Event e;

   while ( _window->pollEvent( e ) )
   {
      switch ( e.type )
      {
         case Event::Closed:
            _window->close();
            break;
         case Event::KeyPressed:
            _inputReader->KeyPressed( e.key.code );
            break;
         case Event::KeyReleased:
            _inputReader->KeyReleased( e.key.code );
            break;
      }
   }

   _inputHandler->HandleInput();
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

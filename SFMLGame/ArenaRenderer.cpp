#include <SFML/Graphics.hpp>

#include "ArenaRenderer.h"
#include "GameConfig.h"
#include "SFMLWindow.h"
#include "Arena.h"
#include "Player.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

ArenaRenderer::ArenaRenderer( shared_ptr<GameConfig> config,
                              shared_ptr<SFMLWindow> window,
                              shared_ptr<Arena> arena ) :
   _window( window ),
   _arena( arena )
{
   auto player = _arena->GetPlayer();

   _playerRect = make_shared<sf::RectangleShape>();
   _playerRect->setSize( Vector2f( player->GetHitBox().width, player->GetHitBox().height ) );
   _playerRect->setFillColor( config->PlayerColor );
}

void ArenaRenderer::Render()
{
   auto player = _arena->GetPlayer();
   _playerRect->setPosition( player->GetPosition() );

   _window->Draw( _playerRect );
}

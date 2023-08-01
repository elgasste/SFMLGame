#include <SFML/Graphics.hpp>

#include "PlayingStateRenderer.h"
#include "GameConfig.h"
#include "RenderConfig.h"
#include "GameData.h"
#include "SFMLWindow.h"
#include "BspOperator.h"

using namespace NAMESPACE;
using namespace std;
using namespace sf;

PlayingStateRenderer::PlayingStateRenderer( shared_ptr<GameConfig> gameConfig,
                                            shared_ptr<RenderConfig> renderConfig,
                                            shared_ptr<GameData> gameData,
                                            shared_ptr<SFMLWindow> window,
                                            shared_ptr<BspOperator> bspOperator ) :
   _gameData( gameData ),
   _window( window ),
   _bspOperator( bspOperator )
{
   _font = make_shared<Font>();
   _font->loadFromFile( renderConfig->MessageFont );

   _text = make_shared<Text>();
   _text->setFont( *_font );
   _text->setCharacterSize( renderConfig->MessageCharSize );
   _text->setFillColor( renderConfig->MessageTextColor );
   _text->setString( "Press ESC for menu, or F12 to toggle diagnostics" );

   _text->setPosition( 12, 0 );
}

void PlayingStateRenderer::Render()
{
   _bspOperator->RenderWorld( _gameData->GetPlayer() );
   _window->Draw( _text );
}

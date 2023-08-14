#pragma once

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Common.h"

NAMESPACE_BEGIN

class RenderData
{
public:
   RenderData( std::shared_ptr<std::map<int, sf::Texture>> textureMap,
               std::shared_ptr<std::map<int, sf::Sprite>> spriteMap );

   sf::Texture& GetTextureById( int id ) { return _textureMap->at( id ); }
   sf::Sprite& GetSpriteById( int id ) { return _spriteMap->at( id ); }

private:
   std::shared_ptr<std::map<int, sf::Texture>> _textureMap;
   std::shared_ptr<std::map<int, sf::Sprite>> _spriteMap;
};

NAMESPACE_END

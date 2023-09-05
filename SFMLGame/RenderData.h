#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderData
{
public:
   RenderData( std::shared_ptr<sf::Texture> playerSpriteTexture );

   std::shared_ptr<sf::Texture> GetPlayerSpriteTexture() const { return _playerSpriteTexture; }

private:
   std::shared_ptr<sf::Texture> _playerSpriteTexture;
};

NAMESPACE_END

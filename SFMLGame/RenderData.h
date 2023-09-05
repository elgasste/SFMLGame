#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class EntitySprite;

class RenderData
{
public:
   std::shared_ptr<sf::Texture> GetPlayerSpriteTexture() const { return _playerSpriteTexture; }
   std::shared_ptr<EntitySprite> GetPlayerSprite() const { return _playerSprite; }

   void SetPlayerSpriteTexture( std::shared_ptr<sf::Texture> texture ) { _playerSpriteTexture = texture; }
   void SetPlayerSprite( std::shared_ptr<EntitySprite> sprite ) { _playerSprite = sprite; }

private:
   std::shared_ptr<sf::Texture> _playerSpriteTexture;

   std::shared_ptr<EntitySprite> _playerSprite;
};

NAMESPACE_END

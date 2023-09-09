#pragma once

#include "Common.h"
#include "EntitySpriteLayer.h"

NAMESPACE_BEGIN

class EntitySprite;

class RenderData
{
public:
   std::shared_ptr<sf::Texture> GetBackgroundTexture() const { return _backgroundTexture; }
   std::shared_ptr<std::map<EntitySpriteLayer, std::shared_ptr<sf::Texture>>> GetPlayerSpriteTextureLayerMap() const { return _playerSpriteTextureLayerMap; }
   std::shared_ptr<EntitySprite> GetPlayerSprite() const { return _playerSprite; }

   void SetBackgroundTexture( std::shared_ptr<sf::Texture> texture ) { _backgroundTexture = texture; }
   void SetPlayerSpriteTextureLayerMap( std::shared_ptr<std::map<EntitySpriteLayer, std::shared_ptr<sf::Texture>>> map ) { _playerSpriteTextureLayerMap = map; }
   void SetPlayerSprite( std::shared_ptr<EntitySprite> sprite ) { _playerSprite = sprite; }

private:
   std::shared_ptr<sf::Texture> _backgroundTexture;
   std::shared_ptr<std::map<EntitySpriteLayer, std::shared_ptr<sf::Texture>>> _playerSpriteTextureLayerMap;
   std::shared_ptr<EntitySprite> _playerSprite;
};

NAMESPACE_END

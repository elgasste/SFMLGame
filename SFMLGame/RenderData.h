#pragma once

#include "Common.h"

NAMESPACE_BEGIN

class RenderData
{
public:
   RenderData( std::shared_ptr<sf::Texture> ballTexture );

   std::shared_ptr<sf::Texture> GetBallTexture() const { return _ballTexture; }

private:
   std::shared_ptr<sf::Texture> _ballTexture;
};

NAMESPACE_END

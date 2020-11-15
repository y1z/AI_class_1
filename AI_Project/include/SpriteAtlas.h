#pragma once
#include "AtlasSegment.h"


/**
 * @file
 * @class SpriteAtlas : represents a collection of sprites .
 */
class SpriteAtlas 
{
public:
  bool
  init(const std::string_view pathToAtlas);
  




  std::shared_ptr<sf::Texture> m_atlas;
};


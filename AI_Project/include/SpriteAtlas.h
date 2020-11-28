#pragma once
#include "AtlasSegment.h"

#include <deque>
#include <filesystem>


/**
 * @class SpriteAtlasDesc : a descriptor for the SpriteAtlas .
 */
struct SpriteAtlasDesc
{
  std::filesystem::path m_pathToFile; 
  std::vector<sf::IntRect>  m_dimensionsOfEachSprite;
};


/**
 * @file
 * @class SpriteAtlas : represents a collection of sprites .
 */
class SpriteAtlas 
{
public:
  using containerType = std::deque<AtlasSegment>;
public:
  /** @returns true when the path is a valid path, returns false otherwise. */
  bool
  init(const SpriteAtlasDesc& atlasDesc);

  /** @returns the total amount of segments in the container. */
  size_t
  getSegmentCount()const;

  /** @returns a pointer to a atlas segment or a nullptr*/
  AtlasSegment&
  getAtlasSegment(const size_t index);

  void
  moveSprite(const Vec2& offset,
             const size_t index);

  void
  setSpriteLocation(const Vec2& pos,
                    const size_t index);

  void
  draw(sf::RenderTarget& target) const;




public:
  /** @brief contains the texture for the atlas */
  std::shared_ptr<sf::Texture> m_atlasTexture = std::make_shared<sf::Texture>();

private:
  /** @brief contains the texture for the atlas */
  containerType m_segments;
};


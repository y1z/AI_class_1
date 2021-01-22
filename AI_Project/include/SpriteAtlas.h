#pragma once
#include "AtlasSegment.h"

#include <deque>
#include <filesystem>


/**
 * @class SpriteAtlasDesc : a descriptor for the SpriteAtlas .
 */
struct SpriteAtlasDesc
{
  SpriteAtlasDesc() = default;
  SpriteAtlasDesc(const SpriteAtlasDesc&) = default;
  SpriteAtlasDesc(SpriteAtlasDesc&&) noexcept = default;

  SpriteAtlasDesc(const std::filesystem::path& path, 
                  const std::vector<sf::IntRect>& dimensionOfEachSprite)
    :m_pathToFile(path),
    m_dimensionsOfEachSprite(dimensionOfEachSprite) 
  {};

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
  [[nodiscard]]bool
  init(const SpriteAtlasDesc& atlasDesc);

  /** @returns the total amount of segments in the container. */
  [[nodiscard]]size_t
  getSegmentCount()const;

  /** @returns a reference to a atlas segment. */
  [[nodiscard]]AtlasSegment&
  getAtlasSegment(const size_t index);

  /** @returns the color of a pixel*/
  [[nodiscard]]sf::Color
  getColorOfPixel(const unsigned x,
                  const unsigned y = 0u)const;

  /** @brief move a individual sprite. */
  void
  moveSprite(const Vec2& offset,
             const size_t index);

  /** @brief sets the position of a sprite. */
  void
  setSpriteLocation(const Vec2& pos,
                    const size_t index);

  void
  setSpriteScale(const Vec2& scale,
                 const size_t index);

  /** 
   *  @brief makes all instance of the given color transparent. 
   *  @param color : the that will be converted to 
   */
  void
  convertColorToAlpha(const sf::Color color)const;

  /** @brief draws the sprites.*/
  void
  draw(sf::RenderTarget& target) const;

 private:
  bool
  internalInit(const SpriteAtlasDesc& atlasDesc);
 public:
  /** @brief contains the texture for the atlas */
  std::shared_ptr<sf::Texture> m_atlasTexture = std::make_shared<sf::Texture>();
  /** @brief contains the individual pixels of the image. */
  std::shared_ptr<sf::Image> m_pixels = std::make_shared<sf::Image>();

 private:
  /** @brief contains the texture for the atlas */
  containerType m_segments;
};


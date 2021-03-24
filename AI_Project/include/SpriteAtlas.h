#pragma once
#include "AtlasSegment.h"

#include <deque>
#include <filesystem>


struct SpriteAtlasDesc;


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

  /** @returns how many */
  [[nodiscard]] size_t
  getAtlasSegmentCount()const;

  /** @returns the color of a pixel*/
  [[nodiscard]]sf::Color
  getColorOfPixel(const unsigned x,
                  const unsigned y = 0u)const;

  /** @returns The path to the sprite */
  [[nodiscard]]const std::string_view
  getPathToSpriteView()const;

  /** @returns The path to the sprite */
  const std::string&
  getPathToSprite()const;

  /** @returns The index of the sprite*/
  uint64
  getIndex()const;

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
  makeColorTransparent(const sf::Color color)const;

  /** @brief draws the sprites.*/
  void
  draw(sf::RenderTarget& target) const;

  /**
   * @returns true when the other object has a LESSER index than the caller.
   */
  constexpr bool
  less(const SpriteAtlas& other)const {
    return m_index < other.m_index;
  }

  /**
   * @returns true when the other object the same index of the caller.
   */
  constexpr bool
  equals(const SpriteAtlas& other)const {
    return m_index == other.m_index;
  }

  /**
   * Calls  SpriteAtlas::less()
   * @copydocs SpriteAtlas::less()
   */
  constexpr bool
  operator<(const SpriteAtlas& other)const {
    return less(other);
  }

  constexpr bool
  operator>(const SpriteAtlas& other)const {
    return !less(other);
  }

  constexpr bool
  operator==(const SpriteAtlas& other)const {
    return equals(other);
  }

 private:

  bool
  internalInit(const SpriteAtlasDesc& atlasDesc);

 private:
  std::string m_pathToSprite;

  /** @brief contains the texture for the atlas */
  containerType m_segments;

  uint64 m_index;
 public:
  /** @brief contains the texture for the atlas */
  std::shared_ptr<sf::Texture> m_atlasTexture = std::make_shared<sf::Texture>();
  /** @brief contains the individual pixels of the image. */
  std::shared_ptr<sf::Image> m_pixels = std::make_shared<sf::Image>();


};


/**
 * @class SpriteAtlasDesc : a descriptor for the SpriteAtlas .
 */
struct SpriteAtlasDesc
{
  SpriteAtlasDesc() = default;
  SpriteAtlasDesc(const SpriteAtlasDesc&) = default;
  SpriteAtlasDesc(SpriteAtlasDesc&&) noexcept = default;

  SpriteAtlasDesc(const std::filesystem::path& path,
                  const std::vector<sf::IntRect>& dimensionOfEachSprite,
                  const std::vector<RotationSegment>& rotationOfEachSprite = {},
                  const uint64 index = 0)
    :
    m_pathToFile(path),
    m_dimensionsOfEachSprite(dimensionOfEachSprite),
    m_rotationOfEachSprite(rotationOfEachSprite),
    m_index(index)
  {};


  SpriteAtlasDesc(std::filesystem::path&& path,
                  std::vector<sf::IntRect>&& dimensionOfEachSprite,
                  std::vector<RotationSegment>&& rotationOfEachSprite = {})
    : m_pathToFile(path),
      m_dimensionsOfEachSprite(dimensionOfEachSprite),
      m_rotationOfEachSprite(rotationOfEachSprite)
  {}
  ~SpriteAtlasDesc() = default;

  SpriteAtlasDesc&
  operator=(const SpriteAtlasDesc&) = default;

  SpriteAtlasDesc&
  operator=(SpriteAtlasDesc&&) = default;

  std::filesystem::path m_pathToFile;
  std::vector<sf::IntRect>  m_dimensionsOfEachSprite;
  std::vector<RotationSegment> m_rotationOfEachSprite;
  uint64 m_index = 0;
};

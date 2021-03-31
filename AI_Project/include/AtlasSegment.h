#pragma once
#include "Racer.h"
#include "RotationSegment.h"
#include <memory>


/**
 * @file
 * @class AtlasSegment : represent a portion of a sprite atlas.
 */
class AtlasSegment
{
public:
  AtlasSegment() = default;
  ~AtlasSegment() = default;
  AtlasSegment(const AtlasSegment&) = default;
  AtlasSegment(AtlasSegment&&)noexcept = default;

public:
  AtlasSegment& operator=(const AtlasSegment&) = default;
  AtlasSegment& operator=(AtlasSegment&&)noexcept = default;

public:
  /** @retruns true if the texture is not null */
  [[nodiscard]]bool
  init(std::shared_ptr<sf::Texture> texture);

  /** @retruns true if the texture is not null */
  [[nodiscard]]bool
  init(std::shared_ptr<sf::Texture> texture,
       const sf::IntRect& rect,
       const RotationSegment& rotation = RotationSegment(0.0f,0.f));

  /** @retruns true if the path is valid, return false when the path is invalid */
  [[nodiscard]]bool
  init(const std::string_view filePath);

  /** @retruns true if the other segment has a texture, return false when the path is invalid */
  [[nodiscard]]bool
  init(const AtlasSegment& other);

  /** @returns the dimensions of the AtlasSegment. */
  sf::IntRect
  getSegmentDimensions()const;

  /** @returns the current size of the AtlasSegment. */
  Vec2
  getSegmentSize()const;

  /** @return false when the segment is goes out side the bound of the sprite. */
  bool
  setSegmentDimension(const Vec2& topLeft,
                      const Vec2& widthAndHeight);

  /** @return false when the segment is goes out side the bound of the sprite. */
  bool
  setSegmentDimension(const sf::IntRect& newDimensions);

  /** @brief move the segment*/
  void
  moveSegment(const Vec2& offset);

  /**
   * @brief controls what the inside the segment by moving inside the atlas.
   * @returns false when the sf::IntRect goes out of bounds of the Atlas,
   * other wise it returns true.
   */
  bool
  offsetSegment(const Vec2& offset);

  /**
   * Draws the current segment
   */
  void
  draw(sf::RenderTarget& target)const;


private:

  /** @brief used to reduce redundancy */
  bool
  internalInit();


  /** @returns true when does not get outside of the bounds of the texture */
  bool
  isRectInsideOfBound(const sf::IntRect& rect)const;

  /** @brief a pointer to the texture. */
  std::shared_ptr< sf::Texture > m_texture;

  /** @brief represents the area of the texture being used. */
  sf::IntRect m_textureRect;
public:
  sf::Sprite m_sprite;
  /**
   * Represents
   */
  RotationSegment m_originalSpriteOritention = RotationSegment(0.0f, 0.0f);
};


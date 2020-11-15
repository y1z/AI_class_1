#pragma once
#include <memory>

#include "Types.h"


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

  /** @retruns true if the path is valid, return false when the path is invalid*/
  bool
  init(const std::string_view filePath);

  bool
  init(const AtlasSegment& other);

  /** @returns the dimensions of the AtlasSegment. */
  sf::IntRect
  getSegmentDimensions()const;


  /** @returns the current size of the AtlasSegment. */
  sf::Vector2i
  getSegmentSize()const;

  /** @return false when the segment is goes out side the bound of the sprite. */
  bool
  setSegmentDimension(const Vec2& topLeft,
                      const Vec2& widthAndHeight);

  /**
   * @brief controls what the inside the segment by moving inside the atlas.
   * @returns false when the sf::IntRect goes out of bounds of the Atlas,
   * other wise it returns true.
   */
  bool
  offsetSegment(const Vec2& offset);

public:
  sf::Sprite m_sprite;
private:
  std::shared_ptr< sf::Texture > m_texture;
};


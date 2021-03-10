#pragma once
#include <random> // for std::rand
#include <cassert> // for assert
#include <array> // for std::array
#include <sstream>
#include <fstream>

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

#include "GameManager.h"
#include "RotationSegment.h"

namespace util {

  /**
   * @returns a value in the range of [minimum ... maximum].
   * @param minimum : the smallest value the function can return.
   * @param maximum : the biggest value the function can return.
   */
  static inline float
  randomRangeFloat(const float minimum,
                   const float maximum) {
   assert(maximum > minimum);
   constexpr static const float inverseMaximum = 1.0f / RAND_MAX;
   const float delta = maximum - minimum;

    return  minimum + (inverseMaximum * std::rand() * delta);
  }

/**
 * @returns a sf::Vector2f vector.
 * @param Vector : the vector that going to be converted.
 */
  static inline sf::Vector2f
  vec2ToVector2f(const Vec2& Vector) {
  return sf::Vector2f(Vector.x, Vector.y);
  }

/** @retruns a sf::Vector2i vector. */
  static inline sf::Vector2i
  vec2ToVector2i(const Vec2& Vector) {
    return sf::Vector2i(static_cast<int>(Vector.x), static_cast<int>(Vector.y));
  }

/** @brief create a line  */
  static inline std::array<sf::Vertex, 2 >
  createLineVertex(const Vec2& startPoint,
                   const Vec2& endPoint,
                   const sf::Color& startColor = sf::Color::White,
                   const sf::Color& endColor = sf::Color::White) {
    return std::array< sf::Vertex, 2>
    {
      sf::Vertex(vec2ToVector2f(startPoint), startColor),
        sf::Vertex(vec2ToVector2f(endPoint), endColor),
    };
  }

/** @returns the points in the four corner. */
  static inline std::array< Vec2, 4>
  getPointsOfIntRect(const sf::IntRect& rect) {
  return
  {
    Vec2(static_cast<float>(rect.left),static_cast<float>(rect.top)),
    Vec2(static_cast<float>(rect.left + rect.width),static_cast<float>(rect.top)),
    Vec2(static_cast<float>(rect.left + rect.width),static_cast<float>(rect.top - rect.height)),
    Vec2(static_cast<float>(rect.left), static_cast<float>(rect.top - rect.height))
  };
}


/** @return a rectangle after being moved*/
  static inline sf::IntRect
  moveIntRect(const sf::IntRect& rect,
              const Vec2& offset) {
    return sf::IntRect(rect.left + offset.x,
                       rect.top + offset.y,
                       rect.width,
                       rect.height);
  }


/**
 * @brief draws a line on to a window.
 * @param startPoint : the starting point of the line.
 * @param endPoint : the ending point of the line.
 */
  void inline static
  drawDebugLine(const Vec2& startPoint,
                const Vec2& endPoint,
                const float scale = 30.0f)

  {
    #if !NDEBUG
    GameManager& gm = GameManager::getInstance();

    const Vec2 delta = (endPoint - startPoint).normalize() * scale;

    gm.addDebugVertexLine(startPoint, endPoint + delta);
    #endif // !NDEBUG

  }


/**
 * @brief changes the scale of a vector to a different scale.
 * @param currentValues : the vector with the raw values.
 * @param currentScale : the scale 'currentVector'
 * @param newDesiredValue : what the values should be changed to.
 */
  sf::Vector2f inline static
  rescaleVector(const sf::Vector2f& currentValues,
                const sf::Vector2f& currentScale,
                const sf::Vector2f& newDesiredValue)
  {
    const sf::Vector2f inverseValue(1.0f / currentValues.x,
                                    1.0f / currentValues.y);

    const sf::Vector2f percentageValue(inverseValue.x * newDesiredValue.x,
                                       inverseValue.y * newDesiredValue.y);

    return sf::Vector2f(currentScale.x * percentageValue.x,
                        currentScale.y * percentageValue.y);
  }

  /**
   * creates a image that twice the width of the original and the other half
   * is mirrored
   *
   * Here is a example of what happens with the image
   *
   * Before:
   *  1 0
   *  1 0
   * After:
   *  0 1 1 0
   *  0 1 1 0
   */
  inline sf::Image
  makeSplitImageWithMirroredHalf(sf::Image& originalImage) {
    sf::Image result;

    const sf::Vector2u originalSize = originalImage.getSize();

    result.create(originalSize.x * 2, originalSize.y, sf::Color(0, 0, 0));

    originalImage.flipHorizontally();

    result.copy(originalImage, 0, 0, sf::IntRect(0, 0, 0, 0), true);

    originalImage.flipHorizontally();

    result.copy(originalImage, originalSize.x, 0);

    return result;
  }

  /**
   * @returns the center point of the rect.
   */
  inline Vec2
  getCenterOfIntRect(const sf::IntRect& rect) {
    const Vec2 topLeft(rect.left, rect.top);
    const Vec2 buttomRight(rect.left + rect.width, rect.top - rect.height);

    const Vec2 halfDistance = (buttomRight - topLeft) * 0.5f;

    return topLeft + halfDistance;
  }

  /**
   * @param [in] topLeft : Where the most top left portion of the image is.
   * @param [in] widthAndHeight : The width and height of each image.
   * @param [in] totalRects : How many rectangles to generate.
   * @param [in] createMirroredSequence : Create another sequence but mirrored.
   *
   */
  inline std::vector<sf::IntRect>
  createHorizontalIntRectSequence(const sf::Vector2i& topLeft,
                                  const sf::Vector2i& widthAndHeight,
                                  const uint32 totalRects,
                                  const bool createMirroredSequence = true) {
    std::vector<sf::IntRect> result;
    const uint32 multiplier = (createMirroredSequence) ? 2u : 1u;
    const size_t realTotalImages = static_cast<size_t>(totalRects * multiplier);

    result.reserve(realTotalImages);

    sf::IntRect currentRectangle(topLeft, widthAndHeight);

    for (uint32 i = 0u; i < totalRects; ++i) {
      result.emplace_back(currentRectangle);
      currentRectangle = moveIntRect(currentRectangle, Vec2(widthAndHeight.x, 0.0f));
    }

    if (createMirroredSequence) {

      currentRectangle = sf::IntRect(topLeft.x, topLeft.y, -widthAndHeight.x, widthAndHeight.y);

      for (uint32 i = 0u; i < totalRects; ++i) {
        result.emplace_back(currentRectangle);
        currentRectangle = moveIntRect(currentRectangle, Vec2(-widthAndHeight.x, 0.0f));
      }

    }

    return result;

  }

  /**
   * @returns A vector containing RotationSegment's that are used to represent
   *  a partial segment of a circular rotation.
   *
   * @param[in] startingAngleRadians The angle where the sequence starts.
   * @param[in] endingAngleRadians Where the sequence ends.
   * @param[in] howManyRotationSegment Controls the amount of rotation segments
   *  to makes NOTE this number is doubled if \p createMirrorSequence is true.
   * @param[in] createMirrorSequence Controls if another sequence that rotates
   *  in the opposite orientation.
   */
  static std::vector<RotationSegment>
  createRotationSegmentSequence(const float startingAngleRadians,
                                const float endingAngleRadians,
                                const uint32 howManyRotationSegment,
                                const bool createMirrorSequence = true)
  {
    std::vector<RotationSegment> result;
    const uint32 reservedSegments = (createMirrorSequence) ?
                                    howManyRotationSegment * 2 :
                                    howManyRotationSegment;
    result.reserve(reservedSegments);

    auto const createSequence = [](const float start, const float end, const uint32 count) {
      RotationSegment currentRotation(start, end);
      std::vector<RotationSegment> sequence;
      sequence.reserve(count);
      const float inverseTotal = 1.f / count;
      const float delta = (end - start) * inverseTotal;
      for (uint32 i = 0u; i < count; ++i) {
        sequence.emplace_back(currentRotation);
        currentRotation.rotateRadians(delta);
      }
      return sequence;
    };

    result = (createSequence(startingAngleRadians,
              endingAngleRadians,
              howManyRotationSegment));

    if (createMirrorSequence) {
      auto temp = createSequence(endingAngleRadians,
                                 startingAngleRadians,
                                 howManyRotationSegment);
      std::move(temp.begin(), temp.end(), std::back_inserter(result));
    }

    return result;
  }

  /**
   * load a file then converts it to a string.
   */
  static std::string
  loadFileToString(std::string_view filePath)
  {
    std::string Result{ "Error" };
    std::ifstream File(filePath.data());

    if( File.is_open() )
    {
      std::stringstream SStream;
      SStream << File.rdbuf();
      Result = SStream.str();
      File.close();
      return Result;
    }
    else
    {
      std::cerr << "Error with path {" << filePath << "}\n";
    }
    return Result;
  }


  /**
   * @returns true when the value in the range [min ... max]
   */
  inline bool
  isInRange(const float min,
            const float max,
            const float value)
  {
    assert((min < max) && "min must be smaller than max");
    return min <= value && value <= max;
  }


}




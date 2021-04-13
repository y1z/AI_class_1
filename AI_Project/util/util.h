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

      currentRectangle = sf::IntRect(topLeft.x, topLeft.y, widthAndHeight.x, widthAndHeight.y);

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
  createRotationSegmentSequence(const RotationSegment& startingAngleRadians,
                                const RotationSegment& endingAngleRadians,
                                const uint32 howManyRotationSegment,
                                const bool createMirrorSequence = true)
  {
    const uint32 reservedSegments = (createMirrorSequence) ?
                                    howManyRotationSegment * 2 :
                                    howManyRotationSegment;
    std::vector<RotationSegment> result;
    result.reserve(reservedSegments);

    auto const createSequence = [](const RotationSegment& m_start,
                                   const RotationSegment& end,
                                   const uint32 count) {
      const float inverseTotal = 1.f / count;
      const float delta = (end.getRotationDelta() * inverseTotal);
      std::vector<RotationSegment> sequence;
      sequence.reserve(count);
      const auto startAngle = m_start.m_start.getAngle();
      RotationSegment currentRotation(startAngle,
                                      startAngle + delta);
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
      const auto oppositeSide
        = RotationSegment(endingAngleRadians).rotateToOppositeQuadrant();
      const auto temp = createSequence(startingAngleRadians,
                                       oppositeSide,
                                       howManyRotationSegment);
      std::move(temp.cbegin(), temp.cend(), std::back_inserter(result));
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



  /**
   * @returns
   *  A string-view that contains the numbers 0..9
   */
  constexpr static std::string_view
  stringViewWithNumbers() {
    return "0123456789";
  }

  /**
   * @returns true when the character passed into the function is a number
   */
  constexpr static bool
  isNumber(const char character) {
    constexpr auto numbers = stringViewWithNumbers();
    for (size_t i = 0u; i < numbers.size(); ++i) {
      if (numbers[i] == character) { return true; }
    }

    return false;
  }


  /**
   * @returns true if the index has a number
   */
  static bool
  isNumber(const sf::String& string,
           uint64 index) {
    static const sf::String numbers(stringViewWithNumbers().data());
    for (size_t i = 0u; i < numbers.getSize(); ++i) {
      if (numbers[i] == string[index]) { return true; }
    }

    return false;
  }

  /**
   * Finds the index of a character that represents a number.
   */
  static uint64
  findNumber(const sf::String& string,
             const uint64 m_start = 0u) {

    for (uint64 i = m_start; i < string.getSize(); ++i) {

      if (isNumber(string, i)) {
        return i;
      }
    }

    return std::numeric_limits<uint64>::max();
  }
  /**
   * @returns
   *  A view into the number of the string.
   *
   * @param[in] stringWitNumbers
   * A string
   */
  static std::string_view
  findFirstNumberInString(const std::string_view stringWithNumbers) {
    constexpr auto numbers = stringViewWithNumbers();
    const size_t firstNumberPos = stringWithNumbers.find(numbers);

    if (std::string_view::npos != firstNumberPos) {
      const size_t stringLen = stringWithNumbers.length();
      size_t lastNumberPos = firstNumberPos;

      for (; lastNumberPos < stringLen; ++lastNumberPos) {
        const bool isCharNumber = isNumber(stringWithNumbers[lastNumberPos]);
        if (isCharNumber)
          continue;
        else {
          break;
        }

      }

      const auto pointerToFistNumber = &stringWithNumbers[firstNumberPos];

      return std::string_view(pointerToFistNumber, lastNumberPos - firstNumberPos);
    }

    return "error";
  }

}




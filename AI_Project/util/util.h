#pragma once
#include <random> // for std::rand
#include <cassert> // for assert 
#include <array> // for std::array

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

#include "GameManager.h" 

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
  constexpr static float inverseMaximum = 1.0f / RAND_MAX;
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
    Vec2(rect.left,rect.top) ,
    Vec2(rect.left + rect.width,rect.top) ,
    Vec2(rect.left + rect.width , rect.top - rect.height) ,
    Vec2(rect.left, rect.top - rect.height)
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

    result.copy(originalImage, 0, 0,sf::IntRect(0,0,0,0),true);

    originalImage.flipHorizontally();

    result.copy(originalImage, originalSize.x, 0);

    return result;
  }



}




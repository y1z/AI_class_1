#pragma once
#include <random> // for std::rand
#include <cassert> // for assert 
#include <array> // for std::array

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

#include "GameManager.h" 

namespace util 
{

  /**
   * @returns a value in the range of [minimum ... maximum]. 
   * @param minimum : the smallest value the function can return.
   * @param maximum : the biggest value the function can return.
   */
  static float
  randomRangeFloat(const float minimum,
                   const float maximum)
  {
    assert(maximum > minimum);
    constexpr static float inverseMaximum = 1.0f / RAND_MAX;
    const float delta = maximum - minimum;

    return  minimum + (inverseMaximum * std::rand() * delta);
  }

  /**
   * @returns a sf::Vector2f vector.
   * @param Vector : the vector that going to be converted.
   */
  static sf::Vector2f
  vec2ToVector2f(const Vec2& Vector)
  {
    return sf::Vector2f(Vector.x, Vector.y);
  }

  static std::array<sf::Vertex, 2 >
  createLineVertex(const Vec2& startPoint,
                   const Vec2& endPoint,
                   const sf::Color& startColor = sf::Color::White,
                   const sf::Color& endColor = sf::Color::White)
  {
    return std::array< sf::Vertex, 2>
    {
      sf::Vertex(vec2ToVector2f(startPoint), startColor),
      sf::Vertex(vec2ToVector2f(endPoint), endColor),
    };
  }


  /**
   * @brief draws a line on to a window.
   * @param startPoint : the starting point of the line.
   * @param endPoint : the ending point of the line.
   */
  void static
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
  sf::Vector2f static
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



}




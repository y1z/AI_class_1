#pragma once
#include <random> // for std::rand
#include <cassert> // for assert 
#include <array> // for std::array

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
namespace util 
{

  /**
   * @returns a value in the range of [minimum ... maximum]. 
   * @param minimum : the smallest value the function can return.
   * @param maximum : the biggest value the function can return.
   */
  static float
  randomRangeFloat(const float minimum, const float maximum)
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


  /**
   * @brief draws a line on to a window.
   * @param startPoint : the starting point of the line.
   * @param endPoint : the ending point of the line.
   * @param window : where the line is going to be drawn.
   */
  void static
  drawLine(const Vec2& startPoint,
           const Vec2& endPoint,
           sf::RenderWindow& window)
  {
    const sf::Vertex line[2]
    {
      sf::Vertex(vec2ToVector2f(startPoint)) ,
      sf::Vertex(vec2ToVector2f(endPoint)) ,
    };

    window.draw(line,
                sizeof(line) / sizeof(sf::Vertex),
                sf::PrimitiveType::LineStrip);
  }

  
}




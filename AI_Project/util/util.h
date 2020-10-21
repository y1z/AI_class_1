#pragma once
#include <random>
#include <cassert>

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
   */
  static sf::Vector2f
  vec2ToVector2f(const Vec2& Vector)
  {
    return sf::Vector2f(Vector.x, Vector.y);
  }
  
}




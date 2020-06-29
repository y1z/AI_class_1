#pragma once
  /**
  * @brief : a namespace that contains global variables
  */
namespace gvar
{
  /**
  * @brief : the value of pi calculated with fractions.
  * // https://www.wired.com/2011/03/what-is-the-best-fractional-representation-of-pi/
  */
  static constexpr float pi = 355.0f / 113.0f;

  /**
  * @brief : twice the value of pi.
  */
  static constexpr float twoPi = pi * 2.0f;

  /**
  * @brief : Represents 3/2 of pi.
  */
  static constexpr float threeHalfsPi = pi * 1.5f;
  /**
  * @brief : pi divided by 2.
  */
  static constexpr float halfPi = pi * .5f;

  /**
  * @brief : 1 fourth of pi.
  */
  static constexpr float quarterPi = pi * .25f;//

  /**
  * @brief : The inverse of pi.
  */
  static constexpr float inversePi = 1.0f / pi;

}

#pragma once
  /**
  * @brief : a namespace that contains global variables
  */
namespace gvars
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
  * @brief :
  */
  static constexpr float threeFourthsPi = pi * 1.5f;
  /**
  * @brief : pi divided by half.
  */
  static constexpr float halfPi = pi * .5f;

  /**
  * @brief : 1 fourth of pi.
  */
  static constexpr float quarterPi = pi * .25f;//
}

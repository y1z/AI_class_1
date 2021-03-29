#pragma once
#include <SFML/System/Vector2.hpp>

/**
 * Math used for finding the position
 */
struct WindowConversion
{
  /**
   * @param[in] percentage
   *  2 normalized values from range [0 ... 1]
   *
   * @returns
   *  The value of the screen based on a normalized value
   *  Example if m_screenWidth = 100 and m_screenHeight = 100
   *  getPositionFromPercentage(sf::Vector2f(0.5f,0.5f) // returns sf::Vector2u(50u,50u)
   */
  static sf::Vector2u
  getPositionFromPercentage(const sf::Vector2u& screenSize,
                            const sf::Vector2f& percentage);

};

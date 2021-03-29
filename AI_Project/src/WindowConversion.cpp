#include "WindowConversion.h"
#include <cassert>
#include <cmath>

sf::Vector2u
WindowConversion::getPositionFromPercentage(const sf::Vector2u& screenSize,
                                            const sf::Vector2f& percentage) {
  assert(!std::signbit(percentage.x) && !std::signbit(percentage.y));
  const float positionInX = percentage.x * screenSize.x;
  const float positionInY = percentage.y * screenSize.y;
  return sf::Vector2u(static_cast<unsigned int>(positionInX),
                      static_cast<unsigned int>(positionInY));
}

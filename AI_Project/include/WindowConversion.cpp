#include "WindowConversion.h"
#include <cassert>

sf::Vector2u
WindowConversion::getPositionFromPercentage(const sf::Vector2u& screenSize,
                                            const sf::Vector2f& percentage) {
  assert(percentage.x <= 0.0f, percentage.y <= 0.f);
  const float positionInX = percentage.x * screenSize.x;
  const float positionInY = percentage.y * screenSize.y;
  return sf::Vector2u(static_cast<unsigned int>(positionInX),
                      static_cast<unsigned int>(positionInY));
}

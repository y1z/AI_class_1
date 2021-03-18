#include "MouseData.h"

void
MouseData::setMousePosition(const sf::Vector2f position) {
  m_mousePosition = position;
}

void
MouseData::setMouseAccion(MOUSE_ACCION::E accion) {
  m_mouseAccion = accion;
}

void
MouseData::setMouseAccion(sf::Mouse::Button accion) {
  m_mouseAccion = convertToMouseAccion(accion);
}

bool
MouseData::isReleased() const {
  return (m_mouseAccion & MOUSE_ACCION::kReleased);
}

bool
MouseData::isPressed() const {
  return (m_mouseAccion | MOUSE_ACCION::kPressing);
}

MOUSE_ACCION::E
MouseData::convertToMouseAccion(sf::Mouse::Button accion) {
  return [](sf::Mouse::Button inAccion) {
    const MOUSE_ACCION::E pressedOrRelease =
      sf::Mouse::isButtonPressed(inAccion)? MOUSE_ACCION::kPressing
                                          : MOUSE_ACCION::kReleased;

    switch (inAccion)
    {
    case sf::Mouse::Left:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kLeftButton | pressedOrRelease);

    case sf::Mouse::Right:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kRightButton | pressedOrRelease);

    case sf::Mouse::Middle:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kMiddleButton | pressedOrRelease);

    case sf::Mouse::XButton1:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kExtraButton1 | pressedOrRelease);

    case sf::Mouse::XButton2:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kExtraButton2 | pressedOrRelease);

    default:
    return static_cast<MOUSE_ACCION::E>(MOUSE_ACCION::kNUll | pressedOrRelease);
    };

  }(accion);
}

#pragma once
#include <SFML/Window/Mouse.hpp>
#include "Vec2.h"

namespace MOUSE_ACCION {
  enum E {
    kNUll = 0x00,
    kLeftButton = 0x01,
    kRightButton = 0x02,
    kMiddleButton = 0x04,

    kExtraButton1 = 0x08,
    kExtraButton2 = 0x10,

    kPressing = 0x20,
    kReleased =  0x40,
  };
}// MOUSE_ACCION

/**
 * Used to represent all relevant data about the mouse.
 */
struct MouseData
{


  void
  setMousePosition(const sf::Vector2f position);

  void
  setMouseAccion(MOUSE_ACCION::E accion);

  /**
   * converts a sf::Mouse::Button to a MOUSE_ACCION .
   */
  void
  setMouseAccion(sf::Mouse::Button accion);

  /**
   * @returns
   *  true is the button is released, otherwise returns false.
   */
  bool
  isReleased()const;

  /**
   * @returns
   *  false is the button is released, otherwise returns true.
   */
  bool
  isPressed()const;

  bool
  isPressedWith(const MOUSE_ACCION::E accion)const;

  bool
  isRelasedWith(const MOUSE_ACCION::E accion)const;

  static MOUSE_ACCION::E
  convertToMouseAccion(sf::Mouse::Button accion);

  Vec2 m_mousePosition = Vec2(0.0f, 0.0f);
  MOUSE_ACCION::E m_mouseAccion = MOUSE_ACCION::kNUll;
};


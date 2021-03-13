#pragma once
#include <vector>

#include "UiRectangle.h"

/**
 * @file
 * @class UiManager : controls the UI.
 */
class UiManager
{
public:
  using RectangleContainer = std::vector< UIRectangle >;
public:

  /**
   * @brief starts the UI Manager.
   */
  bool
  init(const std::vector< UIRectangleDesc >& descriptors);


  /**
   * @brief adds a rectangle
   */
  void
  addRectangle(const UIRectangleDesc& desc);

  /**
   * @brief Changes the size of every single rectangle.
   */
  void
  resizeAllRectangle(const sf::Vector2f& newSize);


  UIRectangle&
  getRectangle(const uint32 index);

  uint32
  getRectangleCount()const;

  void
  draw(sf::RenderTarget& target);

  RectangleContainer::iterator
  begin();

  RectangleContainer::iterator
  end();

private:
  RectangleContainer m_rectangles;
};




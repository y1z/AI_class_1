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
  using RectangleContainer = std::vector< UiRectangle >;
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

  void
  resizeAllRectangle(const sf::Vector2f& newSize);


  UiRectangle& 
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




#pragma once
#include <vector>

#include "UiRectangle.h"
#include "UIText.h"

/**
 * @file
 * @class UiManager : controls the UI.
 */
class UiManager
{
public:
  using RectangleContainer = std::vector< UIRectangle >;

  struct TextElement {
    uint64 index;
    UIText text;
  };

  using TextContainer = std::vector< TextElement >;
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
   * @brief adds a rectangle
   */
  void
  addRectangle(const UIRectangleDesc& rectangleDesc,
               const UITextDescriptor& textDesc);

  /**
   * @brief Changes the size of every single rectangle.
   */
  void
  resizeAllRectangle(const sf::Vector2f& newSize);


  UIRectangle&
  getRectangle(const uint64 index);

  UIText&
  getText(const uint64 index);

  uint64
  getRectangleCount()const;

  uint64
  getTextsCount()const;

  void
  draw(sf::RenderTarget& target);

  RectangleContainer::iterator
  begin();

  RectangleContainer::iterator
  end();

private:
  RectangleContainer m_rectangles;
  TextContainer m_texts;
};




#pragma once
#include "Types.h"

#include <string>
#include <filesystem>

#include <SFML/Graphics/RectangleShape.hpp>

struct UIRectangleDesc 
{
  int32 width;
  int32 height;
  sf::Vector2f position;
  std::string pathToSprite;
};


/**
 * @class UiRectangle : controls all rectangular shaped rectangles.
 */
class UiRectangle 
{
public:
  explicit UiRectangle(const UIRectangleDesc& desc);

  bool
  init(const UIRectangleDesc& desc);

  /** @returns the width of the UI rectangle*/
  int32
  getWidth()const;
  
  /** @returns the height of the UI rectangle*/
  int32
  getHeight()const;


  /** @brief draws the rectangle */
  void
  draw(sf::RenderTarget& target)const;

  /** @returns the scale of the rectangle*/
  sf::Vector2f
  getScale()const;

  /** @returns the scale of the rectangle*/
  sf::Vector2f
  getPosition()const;

  sf::Vector2f
  resizeRectangle(const sf::Vector2f& newSize);


  sf::RectangleShape m_rect;
private:
  std::shared_ptr<sf::Texture> m_texture;
};


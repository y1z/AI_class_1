#pragma once
#include "Racer.h"

#include <string>
#include <filesystem>

#include <SFML/Graphics/RectangleShape.hpp>

struct UIRectangleDesc;
class UIText;


/**
 * @class UIRectangle : controls all rectangular shaped rectangles.
 */
class UIRectangle
{
public:
  UIRectangle() = default;
  explicit UIRectangle(const UIRectangleDesc& desc);


  bool
  operator<(const UIRectangle& other) const;

  bool
  operator>(const UIRectangle& other) const;

  bool
  operator==(const UIRectangle& other) const;

  bool
  operator<=(const UIRectangle& other) const;

  bool
  operator>=(const UIRectangle& other) const;


  bool
  init(const UIRectangleDesc& desc);

  /** @returns the width of the UI rectangle*/
  int32
  getWidth()const;

  /** @returns the height of the UI rectangle*/
  int32
  getHeight()const;

  /** @returns The Width and height of the UI rectangle. */
  sf::Vector2f
  getSize()const;


  /** @brief draws the rectangle */
  void
  draw(sf::RenderTarget& target)const;

  /** @returns the scale of the rectangle*/
  sf::Vector2f
  getScale()const;

  /** @returns the scale of the rectangle*/
  sf::Vector2f
  getPosition()const;

  /** @returns the center of the rectangle*/
  sf::Vector2f
  getCenter()const;

  void
  setPosition(const sf::Vector2f& newPos);

  /** @returns the new scale of the Rectangle*/
  sf::Vector2f
  resizeRectangle(const sf::Vector2f& newSize);

  void
  swapPosition(UIRectangle& otherUI);

  bool
  isInsideRect(const sf::Vector2f& pos)const;


public:
  sf::RectangleShape m_rect;

  Racer* m_ptrRacer;
private:
  std::shared_ptr<sf::Texture> m_texture;
};


struct UIRectangleDesc
{
  UIRectangleDesc()
    :pathToSprite({}),
     position(sf::Vector2f(0.0f, 0.0f)),
     width(100),
     height(100)
  {}

  UIRectangleDesc(const int32 _width,
                  const int32 _height,
                  const sf::Vector2f& _position,
                  const std::string_view _path = "",
                  const sf::Color _color = sf::Color::White)
    :pathToSprite(_path),
     position(_position),
     color(_color),
     width(_width),
     height(_height)
  {}

  UIRectangleDesc(const UIRectangleDesc&) = default;
  UIRectangleDesc(UIRectangleDesc&&) noexcept = default;
  ~UIRectangleDesc() = default;

  UIRectangleDesc& operator = (const UIRectangleDesc&) = default;
  UIRectangleDesc& operator = (UIRectangleDesc&&) noexcept = default;


  std::string pathToSprite;
  sf::Vector2f position;
  sf::Color color;
  int32 width;
  int32 height;
};








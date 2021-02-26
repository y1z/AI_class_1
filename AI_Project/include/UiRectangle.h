#pragma once
#include "Racer.h"

#include <string>
#include <filesystem>

#include <SFML/Graphics/RectangleShape.hpp>

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
                  const std::string_view path)
    :pathToSprite(path),
    position(_position),
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
  int32 width;
  int32 height;
};


/**
 * @class UiRectangle : controls all rectangular shaped rectangles.
 */
class UiRectangle
{
public:
  explicit UiRectangle(const UIRectangleDesc& desc);


  bool
  operator<(const UiRectangle& other) const;

  bool
  operator>(const UiRectangle& other) const;

  bool
  operator==(const UiRectangle& other) const;

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

  /** @returns the center of the rectangle*/
  sf::Vector2f
  getCenter()const;

  void
  setPosition(const sf::Vector2f& newPos);

  /** @returns the new scale of the Rectangle*/
  sf::Vector2f
  resizeRectangle(const sf::Vector2f& newSize);

  void
  swapPosition(UiRectangle& otherUI);

  bool
  isInsideRect(const sf::Vector2f& pos);


public:
  sf::RectangleShape m_rect;

  Racer* m_ptrRacer;
private:
  std::shared_ptr<sf::Texture> m_texture;
};


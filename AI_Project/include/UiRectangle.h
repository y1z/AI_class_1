#pragma once
#include "Types.h"
#include "Boid.h"

#include <string>
#include <filesystem>

#include <SFML/Graphics/RectangleShape.hpp>

struct UIRectangleDesc 
{
  UIRectangleDesc() = default;
  UIRectangleDesc(const int32 _width,
                  const int32 _height,
                  const sf::Vector2f& _position,
                  const std::string_view path)
    :width(_width),
    height(_height),
    position(_position),
    pathToSprite(path)
  {}
  UIRectangleDesc(const UIRectangleDesc& ) = default;
  UIRectangleDesc(UIRectangleDesc&& ) noexcept = default;

  UIRectangleDesc& operator = (const UIRectangleDesc&) = default;
  UIRectangleDesc& operator = (UIRectangleDesc&&) noexcept = default;

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


  bool operator< (const UiRectangle& other) const;

  bool operator> (const UiRectangle& other) const;

  bool operator == (const UiRectangle& other) const;

  bool operator< (const UiRectangle& other);

  bool operator> (const UiRectangle& other);

  bool operator == (const UiRectangle& other);

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


public:
  sf::RectangleShape m_rect;

  Boid* m_ptrBoid;
private:
  std::shared_ptr<sf::Texture> m_texture;
};


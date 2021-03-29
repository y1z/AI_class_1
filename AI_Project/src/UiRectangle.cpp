#include "UiRectangle.h"
#include "util.h"
#include "UIText.h"

#include <SFML/System/FileInputStream.hpp>


UIRectangle::UIRectangle(const UIRectangleDesc &desc)
{
  init(desc);
}

bool
UIRectangle::operator<(const UIRectangle& other) const
{
  return this->m_ptrRacer->m_lapCount < other.m_ptrRacer->m_lapCount;
}

bool
UIRectangle::operator>(const UIRectangle& other) const
{
  return this->m_ptrRacer->m_lapCount > other.m_ptrRacer->m_lapCount;
}

bool
UIRectangle::operator==(const UIRectangle& other) const
{
  return this->m_ptrRacer->m_lapCount == other.m_ptrRacer->m_lapCount;
}

bool
UIRectangle::operator<=(const UIRectangle& other) const {
  return !(this->operator>(other));
}

bool
UIRectangle::operator>=(const UIRectangle& other) const {
  return !(this->operator<(other));
}

bool
UIRectangle::init(const UIRectangleDesc& desc)
{
  m_rect = sf::RectangleShape (sf::Vector2f(desc.width, desc.height));
  m_ptrRacer = nullptr;
  m_texture = std::make_shared<sf::Texture>();

  const sf::Vector2f currentSize = m_rect.getSize();
  m_rect.setOrigin(currentSize.x * 0.5f, currentSize.y * 0.5f);
  sf::FileInputStream fileStream;
  const bool isFileOpen = fileStream.open(desc.pathToSprite);
  bool canLoadFromStream = false;
  if (isFileOpen) {
    canLoadFromStream = m_texture->loadFromStream(fileStream);

    if (canLoadFromStream) {
      m_rect.setTexture(m_texture.get());
    }
  }
  m_rect.setPosition(desc.position);
  m_rect.setFillColor(desc.color);

  return isFileOpen && canLoadFromStream;
}

int32
UIRectangle::getWidth() const
{
  return m_rect.getSize().x;
}

int32
UIRectangle::getHeight() const
{
  return m_rect.getSize().y;
}

sf::Vector2f
UIRectangle::getSize() const {
  return m_rect.getSize();
}

void
UIRectangle::draw(sf::RenderTarget& target) const {
  target.draw(m_rect);
}

sf::Vector2f
UIRectangle::getScale() const
{
  return m_rect.getScale();
}

sf::Vector2f
UIRectangle::getPosition() const
{
  return m_rect.getPosition();
}

sf::Vector2f
UIRectangle::getCenter() const
{
  const sf::FloatRect bounds = m_rect.getLocalBounds();
  const sf::Vector2f centerPosition
  {
    bounds.left + (bounds.width * .5f),
    bounds.top - (bounds.height * .5f)
  };

  return centerPosition;
}

void
UIRectangle::setPosition(const sf::Vector2f& newPos)
{
  m_rect.setPosition(newPos);
}

sf::Vector2f
UIRectangle::resizeRectangle(const sf::Vector2f& newSize)
{
  const sf::Vector2f newScale = util::rescaleVector(m_rect.getSize(),
                                                    m_rect.getScale(),
                                                    newSize);

  m_rect.setScale(newScale);

  return  newScale;
}

void
UIRectangle::swapPosition(UIRectangle& otherUI)
{
  const auto myPos = m_rect.getPosition();
  m_rect.setPosition(otherUI.getPosition());
  otherUI.setPosition(myPos);
}

bool
UIRectangle::isInsideRect(const sf::Vector2f& pos)const {
  auto bound = m_rect.getGlobalBounds();
  sf::Rect temp(pos, { 1,1 });
  return bound.intersects(temp);
}


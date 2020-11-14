#include "UiRectangle.h"
#include "util.h"


#include <fstream>


UiRectangle::UiRectangle(const UIRectangleDesc &desc)
  : m_rect(sf::Vector2f(desc.width, desc.height)),
  m_ptrBoid(nullptr),
  m_texture(std::make_shared<sf::Texture>())
{
  const sf::Vector2f currentSize = m_rect.getSize();
  m_rect.setOrigin(currentSize.x * 0.5f, currentSize.y * 0.5f);
  const std::ifstream file(desc.pathToSprite);
  if( file.is_open() )
  {
    m_texture->loadFromFile(desc.pathToSprite);
    m_rect.setTexture(m_texture.get());
    m_rect.setPosition(desc.position);
  }
}

bool 
UiRectangle::operator<(const UiRectangle& other) const
{
  return this->m_ptrBoid->m_data.m_lapCount < other.m_ptrBoid->m_data.m_lapCount;
}

bool 
UiRectangle::operator>(const UiRectangle& other) const
{
  return this->m_ptrBoid->m_data.m_lapCount > other.m_ptrBoid->m_data.m_lapCount;
}

bool 
UiRectangle::operator==(const UiRectangle& other) const
{
  return this->m_ptrBoid->m_data.m_lapCount == other.m_ptrBoid->m_data.m_lapCount;
}

bool 
UiRectangle::operator<(const UiRectangle& other)
{
  return this->m_ptrBoid->m_data.m_lapCount < other.m_ptrBoid->m_data.m_lapCount;
}

bool UiRectangle::operator>(const UiRectangle& other)
{
  return this->m_ptrBoid->m_data.m_lapCount > other.m_ptrBoid->m_data.m_lapCount;
}

bool 
UiRectangle::operator==(const UiRectangle& other)
{
  return this->m_ptrBoid->m_data.m_lapCount == other.m_ptrBoid->m_data.m_lapCount;
}

bool
UiRectangle::init(const UIRectangleDesc& desc)
{
  m_rect.setSize(sf::Vector2f(desc.width, desc.height));
  m_texture = std::make_shared<sf::Texture>();

  const sf::Vector2f currentSize = m_rect.getSize();
  m_rect.setOrigin(currentSize.x * 0.5f, currentSize.y * 0.5f);
  const std::ifstream file(desc.pathToSprite);
  if( file.is_open() )
  {
    m_texture->loadFromFile(desc.pathToSprite);
    m_rect.setTexture(m_texture.get());
    m_rect.setPosition(desc.position);
    return true;
  }

  return false;
}

int32
UiRectangle::getWidth() const
{
  return m_rect.getSize().x;
}

int32 
UiRectangle::getHeight() const
{
  return m_rect.getSize().y;
}

void 
UiRectangle::draw(sf::RenderTarget& target) const
{
  target.draw(m_rect);
}

sf::Vector2f
UiRectangle::getScale() const
{
  return m_rect.getScale();
}

sf::Vector2f 
UiRectangle::getPosition() const
{
  return m_rect.getPosition(); 
}

sf::Vector2f 
UiRectangle::getCenter() const
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
UiRectangle::setPosition(const sf::Vector2f& newPos)
{
  m_rect.setPosition(newPos);
}

sf::Vector2f 
UiRectangle::resizeRectangle(const sf::Vector2f& newSize)
{
  const sf::Vector2f newScale = util::rescaleVector(m_rect.getSize(),
                                                    m_rect.getScale(),
                                                    newSize);

  m_rect.setScale(newScale);

  return  newScale;
}

void 
UiRectangle::swapPosition(UiRectangle& otherUI)
{
  const auto myPos = m_rect.getPosition();
  m_rect.setPosition(otherUI.getPosition());
  otherUI.setPosition(myPos);
}


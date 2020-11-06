#include "UiRectangle.h"
#include "util.h"


#include <fstream>


UiRectangle::UiRectangle(const UIRectangleDesc &desc)
  : m_rect(sf::Vector2f(desc.width, desc.height)),
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
UiRectangle::resizeRectangle(const sf::Vector2f& newSize)
{
  const sf::Vector2f newScale = util::rescaleVector(m_rect.getSize(),
                                                    m_rect.getScale(),
                                                    newSize);

  m_rect.setScale(newScale);

  return  newScale;
}


#include "AtlasSegment.h"
#include "util.h"
#include <SFML/System/FileInputStream.hpp>

bool
AtlasSegment::init(std::shared_ptr<sf::Texture> texture)
{
  if( texture )
  {
    m_texture = std::move(texture);
    return internalInit();
  }

  return false;
}

bool 
AtlasSegment::init(std::shared_ptr<sf::Texture> texture,
                   const sf::IntRect& rect)
{
  const bool result = init(std::move(texture)) && setSegmentDimension(rect);

  return result;
}

bool
AtlasSegment::init(const std::string_view filePath)
{
  sf::FileInputStream file;
  if( file.open(std::string(filePath)) )
  {
    m_texture = std::make_shared< sf::Texture >();
    m_texture->loadFromStream(file);
    return internalInit();
  }

  return false;
}

bool
AtlasSegment::init(const AtlasSegment& other)
{

  if( other.m_texture )
  {
    m_texture = other.m_texture;
    m_sprite = other.m_sprite; 
    return true;
  }

  return false;
}


sf::IntRect
AtlasSegment::getSegmentDimensions() const
{
  return m_sprite.getTextureRect();
}

Vec2
AtlasSegment::getSegmentSize() const
{
  const auto& rect = m_sprite.getTextureRect();
  return Vec2(rect.width, rect.height);
}

sf::Color 
AtlasSegment::getColorAtPos(unsigned int x, unsigned int y)
{
  return sf::Color();
}

bool 
AtlasSegment::setSegmentDimension(const Vec2& topLeft,
                                  const Vec2& widthAndHeight)
{
  const sf::Vector2i sizeOfTexture = sf::Vector2i(m_texture->getSize());
  const sf::IntRect newRect(util::vec2ToVector2i(topLeft), util::vec2ToVector2i(widthAndHeight));

  if( (newRect.width <= sizeOfTexture.x) && (newRect.height <= sizeOfTexture.y) )
  {
    m_sprite.setTextureRect(newRect);
    const sf::IntRect& currentRect = m_sprite.getTextureRect();
    m_sprite.setOrigin(currentRect.width * 0.5f, currentRect.height * 0.5f);
    return true;
  }

  return false;
}

bool
AtlasSegment::setSegmentDimension(const sf::IntRect& newDimensions)
{
  return setSegmentDimension(Vec2(newDimensions.left, newDimensions.top),
                             Vec2(newDimensions.width, newDimensions.height));
}

void 
AtlasSegment::moveSegment(const Vec2& offset)
{
  m_sprite.move(offset.x, offset.y);
}

bool 
AtlasSegment::offsetSegment(const Vec2& offset)
{
  const sf::IntRect rectAfterBeingMoved = util::moveIntRect(m_sprite.getTextureRect(), offset);
  const bool shouldOffsetSegment = isRectInsideOfBound(rectAfterBeingMoved);
  if( shouldOffsetSegment )
  {
    m_sprite.setTextureRect(rectAfterBeingMoved);
  }

  return shouldOffsetSegment;
}

void 
AtlasSegment::draw(sf::RenderTarget& target) const
{
  target.draw(m_sprite);
}

bool
AtlasSegment::internalInit()
{
  m_sprite.setTexture(*m_texture);
  const sf::IntRect spriteRect = m_sprite.getTextureRect();

  if( sf::IntRect() != m_textureRect )
  {
    m_textureRect = spriteRect;
  }
   
  if( spriteRect.width < 0 || spriteRect.height < 0 )
  {
    return false;
  }

  m_sprite.setOrigin(spriteRect.width * 0.5f, spriteRect.height * 0.5f);

  return true;
}

bool 
AtlasSegment::isRectInsideOfBound(const sf::IntRect& rect) const
{
  const auto pointsInTheRect = util::getPointsOfIntRect(rect);

  for( const auto& point : pointsInTheRect )
  {
    if( !m_textureRect.contains(point.x, point.y) )
    {
      return false;
    }
  }

  return false;
}


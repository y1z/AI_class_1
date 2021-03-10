#include "SpriteAtlas.h"
#include "SFML/System/FileInputStream.hpp"
#include "util.h"

#include <iostream>
#include <cassert>


namespace fsy = std::filesystem;

bool
SpriteAtlas::init(const SpriteAtlasDesc& atlasDesc) {
  const bool isPathToFile =
    fsy::exists(atlasDesc.m_pathToFile) && !fsy::is_directory(atlasDesc.m_pathToFile);

  if (!isPathToFile) {
    std::cerr << '[' << atlasDesc.m_pathToFile
      << "] is not valid, needs to a path to a file.\n\n";
    return isPathToFile;
  }
  else
  {
    return internalInit(atlasDesc);
  }
}

size_t
SpriteAtlas::getSegmentCount() const {
  return m_segments.size();
}

AtlasSegment&
SpriteAtlas::getAtlasSegment(const size_t index) {
  assert(index < m_segments.size() && "out of range for container");
  return m_segments[index];
}

size_t
SpriteAtlas::getAtlasSegmentCount() const {
  return m_segments.size();
}

sf::Color
SpriteAtlas::getColorOfPixel(const unsigned x,
                             const unsigned y)const {
  return  m_pixels->getPixel(x, y);
}

void
SpriteAtlas::moveSprite(const Vec2& offset,
                        const size_t index) {
  auto& refToSegment = getAtlasSegment(index);
  refToSegment.moveSegment(offset);
}

void
SpriteAtlas::setSpriteLocation(const Vec2& pos,
                               const size_t index) {
  auto& refToSegment = getAtlasSegment(index);
  refToSegment.m_sprite.setPosition(util::vec2ToVector2f(pos));
}

void
SpriteAtlas::setSpriteScale(const Vec2& scale,
                            const size_t index) {
  auto& refToSegment = getAtlasSegment(index);
  refToSegment.m_sprite.setScale(scale.x, scale.y);
}



void
SpriteAtlas::makeColorTransparent(const sf::Color color) const {
  m_pixels->createMaskFromColor(color, 0u);

  m_atlasTexture->update(*m_pixels);
}

void
SpriteAtlas::draw(sf::RenderTarget& target) const {
  for (auto& sprite : m_segments) {
    sprite.draw(target);
  }

}

bool
SpriteAtlas::internalInit(const SpriteAtlasDesc& atlasDesc) {

  sf::FileInputStream fileStream;

  if (fileStream.open(atlasDesc.m_pathToFile.generic_string())) {
    m_pixels->loadFromStream(fileStream);
    *m_pixels = util::makeSplitImageWithMirroredHalf(*m_pixels);

    m_atlasTexture->loadFromImage(*m_pixels);

    for (const auto& segmentDimensions : atlasDesc.m_dimensionsOfEachSprite) {
      AtlasSegment segment;
      if (segment.init(m_atlasTexture, segmentDimensions)) {
        m_segments.emplace_back(segment);
      }
      else {
        return false;
      }
    }
  }
  return true;
}





#include "GameMap.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "util.h"
#include <charconv>
#include <fstream>

namespace fs = std::filesystem;

bool
GameMap::loadMap(const std::filesystem::path& pathToMap) {
  bool const isValidPath = !fs::is_directory(pathToMap);
  if (isValidPath) {
    const std::string data = util::loadFileToString(pathToMap.generic_string());

    size_t index = data.find('[');
    while (std::string::npos != index) {
      const float nodeRadius = extractRadiusFrom(data, index);

      index = data.find('<', index);

      const Vec2 nodePosition = extractPositionFrom(data, index);

      index = data.find('[', index);
    }


    return true;
  }



  return false;
}

bool
GameMap::saveMap(const std::string_view saveFilePath) {
  //char bufferForConversion[128];
  //std::memset(bufferForConversion, ' ', sizeof(bufferForConversion));
  //bufferForConversion[127] = '\0';
  std::ofstream file(saveFilePath);

  if (file.is_open()) {

    file << "pos: ";
    for (const auto& elem : m_positionData) {
      file << '[' << elem.m_radius << "]_" << elem.m_position;
    }
    file << "pos;;";
    return true;
  }

  return false;
}

void
GameMap::draw(sf::RenderWindow& window) {
  for(const auto& visual : m_visuals)
  {
    auto* d = visual.get();
    window.draw(*d);
  }
}

void
GameMap::createMap(const std::vector<FollowPathNode>& mapData) {
  for (const auto& elem : mapData) {
    m_positionData.emplace_back(elem);

    sf::CircleShape templateCircle(elem.m_radius);
    const Vec2 center = util::getCenterOfIntRect(templateCircle.getTextureRect());
    templateCircle.setOrigin(center.x, center.y);
    templateCircle.setFillColor(sf::Color::Yellow);
    templateCircle.setPosition(elem.m_position.x, elem.m_position.y);

    auto temp = std::make_unique<sf::CircleShape>(templateCircle);
    m_visuals.emplace_back(std::move(temp));
  }


}

GameMap::mapPathContainer::iterator
GameMap::begin() {
  return m_positionData.begin();
}

GameMap::mapPathContainer::const_iterator
GameMap::cbegin() const {
  return m_positionData.cbegin();
}

GameMap::mapPathContainer::iterator
GameMap::end() {
  return m_positionData.end();
}

GameMap::mapPathContainer::const_iterator
GameMap::cend() const {
  return m_positionData.cend();
}

float
GameMap::extractRadiusFrom(const std::string& data,
                           const size_t currentIndex) const {
  const size_t rightBracketIndex = data.find(']', currentIndex);

  float result;
  const std::from_chars_result extractionData
    = std::from_chars(data.data() + currentIndex + 1, data.data() + rightBracketIndex, result);

  return result;
}

Vec2
GameMap::extractPositionFrom(const std::string& data,
                             const size_t currentIndex) const {

  const size_t separatorPos = data.find(',', currentIndex);
  const size_t secondValueEnd = data.find('>', currentIndex);

  float resultX;
  const std::from_chars_result xValueExtraction
    = std::from_chars(data.data() + currentIndex + 1, data.data() + separatorPos, resultX);

  float resultY;
  const std::from_chars_result yValueExtraction
    = std::from_chars(data.data() + separatorPos + 1, data.data() + (secondValueEnd - 1), resultY);


  return Vec2(resultX, resultY);
}

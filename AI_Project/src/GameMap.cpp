#include "GameMap.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "util.h"
#include <charconv>
#include <fstream>

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

#include "GameMap.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "util.h"
#include <charconv>
#include <fstream>

namespace fs = std::filesystem;
using std::make_unique;

GameMap::GameMap()
  : m_positionData({}),
    //m_visuals(make_unique<sf::Shape>()),
    m_requirements(LapCount(5, 0, 0))

{}

GameMap::~GameMap()
{
  m_positionData.clear();
  m_visuals.clear();
}

bool
GameMap::loadMap(const std::filesystem::path& pathToMap) {
  bool const isValidPath = !fs::is_directory(pathToMap);
  if (isValidPath) {

    if (!m_positionData.empty()) {
      m_positionData.clear();
      m_visuals.clear();
    }

    const std::string data = util::loadFileToString(pathToMap.generic_string());

    {

      size_t index = data.find('[');
      std::vector<FollowPathNode> newPath;

      while (std::string::npos != index) {
        const float nodeRadius = extractRadiusFrom(data, index);

        index = data.find('<', index);

        const Vec2 nodePosition = extractPositionFrom(data, index);

        index = data.find('[', index);
        newPath.emplace_back(FollowPathNode(nodePosition, nodeRadius));
      }

      createMap(std::move(newPath));
    }

    return true;
  }

  return false;
}

bool
GameMap::saveMap(const std::string_view saveFilePath) {

  std::ofstream file(saveFilePath);
  const bool isOperationSuccessful = file.is_open();
  if (isOperationSuccessful) {
    file << "pos: ";
    for (const auto& elem : m_positionData) {
      file << '[' << elem.m_radius << "]_" << elem.m_position;
    }
    file << "pos;;";
  }

  return isOperationSuccessful;
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
  m_positionData.reserve(mapData.size());
  m_visuals.reserve(mapData.size());
  for (const auto& elem : mapData) {
    addNode(elem);
  }

}

void
GameMap::createMap(std::vector<FollowPathNode>&& mapData) {

  createMap(std::forward < const std::vector<FollowPathNode> >(mapData));
}

void
GameMap::addNode(const FollowPathNode& newNode) {
  m_positionData.emplace_back(newNode);

  sf::CircleShape templateCircle(newNode.m_radius);
  const float circleRadius = templateCircle.getRadius();
  templateCircle.setOrigin(circleRadius * .5f, circleRadius * .5f);
  templateCircle.setFillColor(sf::Color::Yellow);
  templateCircle.setPosition(newNode.m_position.x, newNode.m_position.y);

  auto temp = std::make_unique<sf::CircleShape>(templateCircle);
  m_requirements.m_totalCheckPoint += 1u;
  m_visuals.emplace_back(std::move(temp));
}

void
GameMap::clear() {
  m_positionData.clear();
  m_visuals.clear();
}

LapCount
GameMap::getLapRequiements() const {
  return m_requirements;
}

const GameMap::mapPathContainer&
GameMap::getPathContainer()const {
  return m_positionData;
}

const GameMap::visualsContainer&
GameMap::getVisualContainer()const {
  return m_visuals;
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
    = std::from_chars(data.data() + separatorPos + 2, data.data() + (secondValueEnd), resultY);


  return Vec2(resultX, resultY);
}

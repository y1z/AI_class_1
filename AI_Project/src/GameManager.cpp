#include "GameManager.h"
#include "util.h"
#include "Racer.h"
#include "GameMap.h"

#include <cassert>


bool
GameManager::init(const GameMap& gameMap) {

  auto requiements = gameMap.getLapRequiements();
  const auto totalCheckpoints = gameMap.getPathContainer().size() * requiements .m_fullLap;
  requiements.m_checkPointsRequiredForFullLap = gameMap.getPathContainer().size();
  m_lapRequirements = requiements;
  return true;
}

void
GameManager::OnShutDown()
{
  m_groupAgents.clear();
  m_path.m_pathData.clear();
}

int
GameManager::OnStartUp(void* _Desc)
{
  m_path.m_vertexArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
#if !NDEBUG
  m_debugLines.setPrimitiveType(sf::PrimitiveType::LineStrip);
#endif // !NDEBUG

  if( nullptr != _Desc )
  {
    auto descriptor = reinterpret_cast<GameManagerDescriptor*>(_Desc);
    assert(nullptr != descriptor);

    auto& nodeContainer = descriptor->m_pathData;

    m_path.m_vertexArray.resize(nodeContainer.size());

    for (const auto& pathNode : nodeContainer) {
      m_path.m_vertexArray.append(util::vec2ToVector2f(pathNode.m_position));
    }

    for (auto& boidDesc : descriptor->m_boidDescriptors) {
      m_groupAgents.emplace_back(Boid(boidDesc));
    }
    return 0;
  }

  return -1;
}

void
GameManager::setupGroup()
{
  for( auto& agents : m_groupAgents )
  {
    agents.getBoid().m_data.m_groupOfRacers = &m_groupAgents;
  }

}

size_t
GameManager::addRacerToGame(const BoidDescriptor& descriptor)
{
  return addRacerToGame(Racer(descriptor));
}

size_t
GameManager::addRacerToGame(const BoidDescriptor& descriptor,
                            SpriteAtlas* atlas) {
  const size_t boidIndex = addRacerToGame(descriptor) - 1u;
  auto& agent = m_groupAgents[boidIndex];
  agent.m_atlasPtr = atlas;

  return boidIndex;
}

size_t
GameManager::addRacerToGame(const Boid& newBoid)
{
  return addRacerToGame(Racer(newBoid));
}

size_t
GameManager::addRacerToGame(const Racer& racer)
{
  m_groupAgents.emplace_back(racer);
  return m_groupAgents.size();
}

void
GameManager::addNodeToGlobalPath(const FollowPathNode& node) {

  m_path.m_pathData.emplace_back(node);
  sf::CircleShape circle(node.m_radius);

  circle.setPosition(node.m_position.x, node.m_position.y);
  circle.setFillColor(sf::Color::Yellow);

  m_path.m_pointsInPath.emplace_back(circle);
  m_path.m_vertexArray.append(sf::Vertex(util::vec2ToVector2f(node.m_position),
                              sf::Color::Red));

  m_lapRequirements.m_checkPointsRequiredForFullLap += 1u;
}

void
GameManager::setLapTotal(const uint32 requiredLapCount)
{
  m_lapRequirements.m_fullLap = requiredLapCount;
}

void
GameManager::setLapCount(const LapCount required) {
  m_lapRequirements = required;
}

bool
GameManager::removeBoidFromGame(const size_t index)
{
  auto& nodeContainer = m_path.m_pathData;
  if( nodeContainer.size() - 1 >= index )
  {
    nodeContainer.erase(nodeContainer.begin() + index);
    return true;
  }
  return false;
}

LapCount
GameManager::getLapRequirements() const
{
  return m_lapRequirements;
}

size_t
GameManager::getTotalBoids() const
{
  return m_path.m_pathData.size();
}

GameManager::AgentType&
GameManager::getAgentRef(const size_t index)
{
  assert(m_groupAgents.size() - 1 >= index);
  return m_groupAgents[index];
}

GameManager::AgentType*
GameManager::getAgentPtr(const size_t index)
{
  assert(m_groupAgents.size() - 1 >= index);
  return &m_groupAgents[index];
}

const GameManager::containerType&
GameManager::getAgentContainerRef() const
{
  return m_groupAgents;
}

GameManager::containerType&
GameManager::getAgentContainerRef()
{
  return m_groupAgents;
}

const FollowPath::PathContainer&
GameManager::getPathContainerRef() const
{
  return m_path.m_pathData;
}

FollowPath::PathContainer
GameManager::getPathContainerRef()
{
  return m_path.m_pathData;
}

void
GameManager::drawPath(sf::RenderWindow& window) const
{
  window.draw(m_path.m_vertexArray);
  for( const auto& shape : m_path.m_pointsInPath )
  {
    window.draw(shape);
  }
}

void
GameManager::drawRacers(sf::RenderWindow& window) {
  for (auto& boid : m_groupAgents) {
    boid.draw(window);
  }
}

void
GameManager::addDebugVertexLine(const Vec2& start,
                                const Vec2& end)
{
  const sf::Vertex lineStart(util::vec2ToVector2f(start), sf::Color::White);
  const sf::Vertex lineEnd(util::vec2ToVector2f(end), sf::Color::White);

  addDebugVertexLine(lineStart, lineEnd);
}

void
GameManager::addDebugVertexLine(const sf::Vertex& startOfLine,
                                const sf::Vertex& endOfLine)
{
#if !NDEBUG
  m_debugLines.append(startOfLine);
  m_debugLines.append(endOfLine);
#endif // !NDEBUG

}

void
GameManager::drawAndClearDebug(sf::RenderWindow& window)
{
#if !NDEBUG

  window.draw(m_debugLines);
  m_debugLines.clear();

#endif // !NDEBUG

}


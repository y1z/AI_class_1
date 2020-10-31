#include "GameManager.h"
#include "util.h"

#include <cassert>


void
GameManager::OnShutDown()
{
  m_groupBoids.clear();
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
    GameManagerDescriptor* descriptor = static_cast<GameManagerDescriptor *>(_Desc);
    assert(nullptr != descriptor);

    auto& nodeContainer = m_path.m_pathData;
    nodeContainer = std::move(descriptor->m_pathData);
    m_path.m_vertexArray.resize(nodeContainer.size());

    for( const auto& pathNode : nodeContainer )
    {
      m_path.m_vertexArray.append(util::vec2ToVector2f(pathNode.m_position));
    }

    for( auto& boidDesc : descriptor->m_boidDescriptors )
    {
      m_groupBoids.emplace_back(Boid(boidDesc));
    }
    return 0;
  }

  return -1;
}

void
GameManager::setupGroup()
{
  for(auto& boid : m_groupBoids )
  {
    boid.m_data.m_groupOfBoids = &m_groupBoids;
  }

}

size_t
GameManager::addBoidToGame(const BoidDescriptor& descriptor)
{
  return addBoidToGame(Boid(descriptor));
}

size_t
GameManager::addBoidToGame(const Boid& newBoid)
{
  m_groupBoids.emplace_back(newBoid);
  return m_groupBoids.size();
}

void
GameManager::addNodeToGlobalPath(const FollowPathNode& node )
{

  auto& nodeContainer = m_path.m_pathData;
  nodeContainer.emplace_back(node);
  sf::CircleShape circle(node.m_radius);
  circle.setPosition(node.m_position.x, node.m_position.y);
  circle.setFillColor(sf::Color::Yellow);
  m_path.m_pointsInPath.emplace_back(circle);
  m_path.m_vertexArray.append(sf::Vertex(util::vec2ToVector2f(node.m_position),
                              sf::Color::Red));
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

size_t
GameManager::getTotalBoids() const
{
  return m_path.m_pathData.size();
}

Boid&
GameManager::getBoidRef(const size_t index)
{
  assert(m_groupBoids.size() - 1 >= index);
  return m_groupBoids[index];
}

Boid*
GameManager::getBoidPtr(const size_t index)
{
  assert(m_groupBoids.size() - 1 >= index);
  return &m_groupBoids[index];
}

const GameManager::containerType&
GameManager::getBoidContainerRef() const
{
  return m_groupBoids;
}

GameManager::containerType&
GameManager::getBoidContainerRef()
{
  return m_groupBoids;
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
  m_debugLines.append(startOfLine);
  m_debugLines.append(endOfLine);
}

void
GameManager::drawAndClearDebug(sf::RenderWindow& window)
{
  window.draw(m_debugLines);
  m_debugLines.clear();
}


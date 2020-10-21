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

  m_vertexArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
  if( nullptr != _Desc )
  {
    GameManagerDescriptor* descriptor = reinterpret_cast< GameManagerDescriptor* >(_Desc);
    assert(nullptr != descriptor);

    auto& nodeContainer = m_path.m_pathData;
    nodeContainer = std::move(descriptor->m_pathData);
    m_vertexArray.resize(nodeContainer.size());

    for( const auto& pathNode : nodeContainer )
    {
      m_vertexArray.append(util::vec2ToVector2f(pathNode.m_position));
    }

    for( auto& boidDesc : descriptor->m_boidDescriptors )
    {
      m_groupBoids.emplace_back(Boid(boidDesc));
    }
    return 0;
  }

  return -1;
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
GameManager::addNodeToGlobalPath(const FollowPathNode& node)
{

  auto& nodeContainer = m_path.m_pathData;
  nodeContainer.emplace_back(node); 
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

GameManager::containerType::iterator
GameManager::begin()
{
  return m_groupBoids.begin();
}

GameManager::containerType::iterator
GameManager::end()
{
  return m_groupBoids.end();
}

GameManager::containerType::const_iterator
GameManager::cbegin() const 
{
  return m_groupBoids.cbegin();
}

GameManager::containerType::const_iterator
GameManager::cend() const
{
  return m_groupBoids.cend(); 
}

void 
GameManager::drawPath(sf::RenderWindow& window) const
{
  window.draw(m_vertexArray);
}



#include "GameManager.h"

#include <cassert>


void 
GameManager::OnShutDown()
{
  m_groupBoids.clear();
  m_globalPath.clear();
}

int
GameManager::OnStartUp(void* _Desc)
{
  if( nullptr != _Desc )
  {
    GameManagerDescriptor* descriptor = reinterpret_cast< GameManagerDescriptor* >(_Desc);
    assert(nullptr != descriptor);

    m_globalPath = std::move(descriptor->m_path);

    for(auto& boidDesc : descriptor->m_boidDescriptors )
    {
      m_groupBoids.emplace_back(Boid(boidDesc));
    }
    return 0;
  }

  return -1;
}

size_t
GameManager::addBoidToGame(BoidDescriptor& descriptor)
{
  Boid newBoid(descriptor);
  return addBoidToGame(newBoid);
}

size_t
GameManager::addBoidToGame(Boid& newBoid)
{
  m_groupBoids.emplace_back(newBoid);
  return m_groupBoids.size();
}

bool 
GameManager::removeBoidFromGame(const size_t index)
{
  if(m_groupBoids.size() - 1 >= index )
  {
    m_groupBoids.erase(m_groupBoids.begin() + index);
    return true;
  }
  return false;
}

size_t
GameManager::getTotalBoids() const
{
  return m_groupBoids.size();
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

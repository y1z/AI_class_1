#include "GameManager.h"

#include <cassert>


void 
GameManager::OnShutDown()
{
  m_boids.clear();
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
      m_boids.emplace_back(Boid(boidDesc));
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
  m_boids.emplace_back(newBoid);
  return m_boids.size();
}

bool 
GameManager::removeBoidFromGame(const size_t index)
{
  if(m_boids.size() - 1 >= index )
  {
    m_boids.erase(m_boids.begin() + index);
    return true;
  }
  return false;
}

size_t
GameManager::getTotalBoids() const
{
  return m_boids.size();
}

Boid&
GameManager::getBoidRef(const size_t index)
{
  assert(m_boids.size() - 1 >= index);
  return m_boids[index];
}

Boid*
GameManager::getBoidPtr(const size_t index)
{
  assert(m_boids.size() - 1 >= index);
  return &m_boids[index];
}

std::deque<Boid>::iterator 
GameManager::begin()
{
  return m_boids.begin();
}

std::deque<Boid>::iterator 
GameManager::end()
{
  return m_boids.end();
}

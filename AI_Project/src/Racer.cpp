#include "Racer.h"
#include "GameManager.h"

Racer::Racer(const BoidDescriptor& desc)
:m_boid(desc),
m_lapCount(LapCount())
{}

Racer::Racer(const Boid& boid)
  :m_boid(boid),
  m_lapCount(LapCount())
{}

BoidDescriptor&
Racer::getBoidData()
{
  return m_boid.m_data;
}

const BoidDescriptor&
Racer::getBoidData() const
{
  return m_boid.m_data;
}

Boid&
Racer::getBoid()
{
  return m_boid;
}

const Boid&
Racer::getBoid() const
{
  return m_boid;
}

uint32 
Racer::getTotalLap() const
{
  return m_lapCount.m_fullLap;
}

LapCount 
Racer::getLapRequirements() const
{
  return m_lapCount;
}

uint32
Racer::getCheckpointTotal() const
{
  return m_lapCount.m_totalCheckPoint;
}

uint32
Racer::getCurrentLapCheckPoint() const
{
  return m_lapCount.m_currentCheckPoints;
}

void
Racer::update(float deltaTime)
{
  m_boid.update(deltaTime);
  const bool shouldUpdateLapCount = m_boid.m_data.m_nodesReached > 0u;
  if( shouldUpdateLapCount )
  {
    this->updateLapCount();
  }
}

void 
Racer::draw(sf::RenderTarget& target)
{
  m_boid.draw(target);
}

void 
Racer::destroy()
{
  m_boid.destroy();
}

void 
Racer::updateLapCount()
{
  m_lapCount.m_currentCheckPoints += 1u;
  m_lapCount.m_totalCheckPoint += 1u;
  GameManager& gm = GameManager::getInstance(); 
  const LapCount lapRequirements = gm.getLapRequirements();
  const bool hasFinishedLap = 
    (m_lapCount.m_currentCheckPoints >= lapRequirements.m_currentCheckPoints);
  if( hasFinishedLap )
  {
    m_lapCount.m_currentCheckPoints = 0u;
    m_lapCount.m_fullLap += 1u;
  }

}


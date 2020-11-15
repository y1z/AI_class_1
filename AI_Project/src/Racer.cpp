#include "Racer.h"

Racer::Racer(const BoidDescriptor& desc)
:m_boid(desc)
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
Racer::getLapCount() const
{
  return m_lapCount.m_fullLap;
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
}

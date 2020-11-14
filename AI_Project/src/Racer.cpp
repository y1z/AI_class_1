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

void
Racer::update(float deltaTime)
{
  m_boid.update(deltaTime);
}

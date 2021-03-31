#include "Racer.h"
#include "GameManager.h"
#include <cassert>

Racer::Racer(const BoidDescriptor& desc)
  :m_atlasPtr(nullptr),
  m_currentFrame(0u),
  m_boid(desc),
  m_lapCount(LapCount())
{}

Racer::Racer(const Boid& boid)
  :m_atlasPtr(nullptr),
  m_currentFrame(0u),
  m_boid(boid),
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
  return m_lapCount.m_checkPointsRequiredForFullLap;
}

size_t
Racer::getCurrentFrame() const {
  return m_currentFrame;
}

void
Racer::setFrame(const int32 selectedFrame) {
  assert(selectedFrame < this->m_atlasPtr->getAtlasSegmentCount());
  m_atlasPtr->setSpriteLocation(Vec2(std::numeric_limits<float>::lowest(),
                                std::numeric_limits<float>::lowest()),
                                m_currentFrame);

  m_currentFrame = selectedFrame;
}

void
Racer::advanceFrames(const int32 framesToAdvance) {
  const size_t totalSegments = m_atlasPtr->getAtlasSegmentCount();

  m_atlasPtr->setSpriteLocation(Vec2(std::numeric_limits<float>::lowest(),
                                std::numeric_limits<float>::lowest()),
                                m_currentFrame);

  m_currentFrame = (( m_currentFrame + framesToAdvance) % totalSegments);
  std::cout << "current frame [" << m_currentFrame << "] ";
}

void
Racer::update(float deltaTime)
{
  m_boid.update(deltaTime);
  if( m_atlasPtr != nullptr )
  {
    //m_boid.getDir().getAngle();
    m_atlasPtr->setSpriteLocation(m_boid.m_data.m_position, m_currentFrame);
  }
  if( m_boid.m_data.m_hasReachedNode )
  {
    this->updateLapCount();
  }
}

void
Racer::selectFrameBasedOnRotation() const {
  assert(nullptr != m_atlasPtr && "Requires that the racer have a sprite");
  const Vec2 direction = m_boid.getDir();
  direction.getAngle();

}

void
Racer::draw(sf::RenderTarget& target)
{
  if( nullptr != m_atlasPtr )
  {
    const auto boidSize = m_boid.m_data.m_boidSize;
    m_atlasPtr->setSpriteScale(Vec2(1.0f, 1.0f), m_currentFrame);
    m_atlasPtr->setSpriteLocation(m_boid.m_data.m_position, m_currentFrame);
    m_atlasPtr->draw(target);
  }
  else
  {
    m_boid.draw(target);

  }
}

void
Racer::destroy()
{
  m_boid.destroy();
}

void
Racer::updateLapCount()
{
  m_lapCount.m_checkPointsRequiredForFullLap += 1u;
  m_lapCount.m_totalCheckPoint += 1u;
  GameManager& gm = GameManager::getInstance();
  const LapCount lapRequirements = gm.getLapRequirements();
  const bool hasFinishedLap =
    (m_lapCount.m_checkPointsRequiredForFullLap >= lapRequirements.m_checkPointsRequiredForFullLap);
  if( hasFinishedLap )
  {
    m_lapCount.m_checkPointsRequiredForFullLap = 0u;
    m_lapCount.m_fullLap += 1u;
  }
}



#include "FrameData.h"
#include <cmath>

namespace chrono = std::chrono;


FrameData::FrameData()
  :m_frames(frameContainer()),
  m_currentTime(0.0f),
  m_animationLengthTime(Frame::illDefineTime)
{}

FrameData::FrameData(const frameContainer& frames)
  :m_frames(frames),
  m_currentTime(0.0f),
m_animationLengthTime(Frame::illDefineTime)
{
  internalSort();
}


FrameData::FrameData(frameContainer&& frames)
  : m_frames(std::forward<frameContainer>(frames)),
  m_currentTime(0.0f),
  m_animationLengthTime(Frame::illDefineTime)
{
  internalSort();
}

bool
FrameData::init(const frameContainer& frames)
{
  m_frames = frames;
  internalSort();
  m_animationLengthTime = getAnimationLength();
  return true;
}

float
FrameData::update(const float deltaTime)
{
  m_currentTime = std::fmodf(m_currentTime + deltaTime, m_animationLengthTime);
  const Frame* ptrFrame = getCurrentFrame();

  return m_currentTime;
}

void
FrameData::internalSort()
{
  std::sort(std::begin(m_frames), std::end(m_frames));
}

const Frame*
FrameData::getCurrentFrame()
{
  for( const auto& frame : m_frames )
  {
    if(frame.isInTimeRange(m_currentTime))
    {
      return &frame;
    }
  }
  return nullptr; 
}

float
FrameData::getAnimationLength() const
{
  return m_frames.at(m_frames.size() - 1).m_endingTime;
}

#include "FrameData.h"

FrameData::FrameData(const sf::IntRect& _frameSize,
                     const frameTime _startingTime,
                     const frameTime _endingTime)
  :m_frameSize(_frameSize),
  m_startingTime(std::chrono::duration_cast< conversionTime >(_startingTime).count()),
  m_endingTime(std::chrono::duration_cast< conversionTime >(_endingTime).count())
{}

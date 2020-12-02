#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <chrono>
/**
 * @file
 * @class FrameData : used for knowing how to animate a character;
 */
class FrameData 
{
public:
  using frameTime = std::chrono::milliseconds;
  using conversionTime = std::chrono::duration<float, std::chrono::seconds>;
public:

  FrameData(const sf::IntRect& _frameSize,
            const frameTime _startingTime,
            const frameTime _endingTime);


  sf::IntRect m_frameSize;

  float m_startingTime;
  float m_endingTime;
};


#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <chrono>
#include <vector>

class Racer;

/** @brief a descriptor for animation. */
struct Frame 
{
  static constexpr float illDefineTime = -1.0f;
  
  Frame()
    :m_frameSize(sf::IntRect({ 0,0 }, { 1,1 })),
    m_ptrToRacer(nullptr),
    m_startingTime(illDefineTime),
    m_endingTime(illDefineTime)
  {}

  Frame(const sf::IntRect& frameSize,
        const Racer* ptrToRacer,
        const float startingTime,
        const float endingTime)
    :m_frameSize(frameSize),
    m_ptrToRacer(ptrToRacer),
    m_startingTime(startingTime),
    m_endingTime(endingTime)
  {}

  constexpr bool 
  operator<(const Frame& other) const
  {
    return m_startingTime < other.m_startingTime;
  }

  constexpr bool 
  operator>(const Frame& other) const
  {
    return m_startingTime > other.m_startingTime;
  }

  constexpr bool
  isInTimeRange(const float time)const
  {
    return m_startingTime <= time && m_endingTime >= time; 
  }


  sf::IntRect m_frameSize;   
  const Racer* m_ptrToRacer = nullptr;
  float m_startingTime;
  float m_endingTime;
};


/**
 * @file
 * @class FrameData : used for knowing how to animate a character;
 */
class FrameData
{
public:
  using frameContainer = std::vector<Frame>;
  using conversionTime = std::chrono::duration<float, std::chrono::seconds>;
public:
  FrameData();

  FrameData(const frameContainer& frames);


  FrameData(frameContainer &&frames);

public:
  /**
   * @returns true on success, false on failure.
   * @param frames : 
   */
  bool
  init(const frameContainer& frames);

  /**
   * @brief updates the animation.
   */
  float 
  update(const float deltaTime);

  const Frame*
  getCurrentFrame();
private:

  void
  internalSort();

  /** @returns the length of the animation. */
  float
  getAnimationLength()const;

public:
  frameContainer m_frames;
  float m_currentTime;
private:
  float m_animationLengthTime;
};


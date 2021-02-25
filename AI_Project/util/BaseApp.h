#pragma once
#include "Timer.h"
#include "Racer.h"

/**
* @brief Defines an interface from which many app can be run.
*/
class BaseApp
{
public:// constructors
  BaseApp()
    :m_timer(Timer()),
    m_deltaTime(0.0f),
    m_screenWidth(1280u),
    m_screenHeight(720u)
  {}

  virtual ~BaseApp() = default;

  /**
  * @brief The interface of the app.
  * @bug no known bugs.
  */
  virtual int run(unsigned int screenWith = 1280u,
                  unsigned int screenHeight = 720u) = 0;
protected:

  /**
  * @brief where the main loop occurs
  * @bug no known bugs.
  */
  virtual int mainLoop() = 0;

protected:
  Timer m_timer;
  float m_deltaTime;
  unsigned int m_screenWidth;
  unsigned int m_screenHeight;
};

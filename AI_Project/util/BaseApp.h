#pragma once
#include "Timer.h"

/**
* @brief Defines an interface from which many app can be run.
*/
class BaseApp 
{
public:// constructors
  BaseApp()
    :m_timer(Timer()),
    m_deltaTime(0.0f)
  {}

  virtual ~BaseApp() = default;

  /**
  * @brief Starts the app
  * @bug no known bugs.
  */
  virtual int run() = 0;
protected:

  virtual int mainLoop() = 0;

  Timer m_timer;
  float m_deltaTime;

};

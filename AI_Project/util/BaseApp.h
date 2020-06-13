#pragma once
#include "Timer.h"

/**
* @brief Defines an interface from which many app can be run.
*/
class BaseApp 
{
public:
  BaseApp() = default;
  virtual ~BaseApp() = default;
  virtual int run() = 0;
protected:
  Timer m_timer;
  float m_deltaTime;

};

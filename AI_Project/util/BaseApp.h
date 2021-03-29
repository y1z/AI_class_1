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
    m_screen({ 1280u, 720u })
  {}

  virtual ~BaseApp() = default;

  /**
  * @brief The interface of the app.
  * @bug no known bugs.
  */
  virtual int run(unsigned int screenWith = 1280u,
                  unsigned int screenHeight = 720u) = 0;

  virtual void closeWindow() = 0;
protected:

  /**
  * @brief where the main loop occurs
  * @bug no known bugs.
  */
  virtual int mainLoop() = 0;

  /**
   * @returns
   *  The width of the screen.
   */
  unsigned int
  getScreenWidth()const {
    return m_screen.comp.width;
  }


  /**
   * @returns
   *  The height of the screen.
   */
  unsigned int
  getScreenHeight()const {
    return m_screen.comp.height;
  }

  union screen
  {
    struct components
    {
      unsigned int width;
      unsigned int height;
    };
    unsigned int size[2];
    components comp;
  };

protected:
  Timer m_timer;
  float m_deltaTime;
  screen m_screen;
};

#pragma once
#include "BaseApp.h"
#include "Boid.h"

#include <memory>

/**
* @brief Defines an app used to test the Boids.
*/
class TestBoidApp final : public BaseApp
{
public:
  TestBoidApp() = default;
  ~TestBoidApp() = default;
  
  int
  run() override;
 
private:

  /**
  * @brief Initializes all the variables used by the app.
  * @bug no known bugs.
  */
  int 
  init();

  /**
  * @brief Takes care of handling user input.
  * @bug no known bugs.
  */
  void 
  handleInput();

  /**
  * @brief Takes care of all boid related operations.
  * @bug no known bugs.
  */
  void
  handleBoids();


  /**
  * @brief Takes care of everything related with drawing on the screen.
  * @bug no known bugs.
  */
  void
  handleRendering();

  /**
  * @brief Contains the main Loop of the app.
  * @bug no known bugs.
  */
  int
  mainLoop()override;
  
private:

  Boid m_mousePosition;

  std::unique_ptr<Boid> m_boid;

  std::unique_ptr<sf::RenderWindow> m_window;

  std::vector<Boid> m_groupBoids;

  std::vector<FollowPathNode> m_path;

};


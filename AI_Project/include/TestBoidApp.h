#pragma once
#include "BaseApp.h"
#include "Boid.h"

#include <vector>
#include <memory>

/**
* @brief Defines an app used to test the Boids.
*/
class TestBoidApp : public BaseApp
{
public:
  
  int run() override;
private:

  int init();


  int loop();
  
  std::unique_ptr<Boid> m_boid;

  std::unique_ptr<sf::RenderWindow> m_window;

};


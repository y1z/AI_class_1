#pragma once

#include "BaseApp.h"
#include <SFML/Graphics.hpp>
#include <memory>

class StateMachineTestApp :
  public BaseApp
{

public:
  int 
  run() override;
private:

  int 
  start();

  int
  mainLoop()override;

  void
  handleInput();

private://variables

  unsigned int m_screenWidth = 900;
  unsigned int m_screenHeight = 900;

  std::unique_ptr<sf::RenderWindow> m_window;
};


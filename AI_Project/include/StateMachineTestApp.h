#pragma once
#include "BaseApp.h"
#include "FSM.h"

#include <SFML/Graphics.hpp>
#include <memory>


class StateMachineTestApp final :
  public BaseApp
{

public:
  /**
  * @brief The function that starts the app.
  */
  int
  run(unsigned int screenWith,
      unsigned int screenHeight) override;
private:

  int 
  init();

  /**
  * @brief 
  */
  int
  mainLoop()override;

  void
  handleInput();

  void
  handleRender();

private://variables
  std::unique_ptr<sf::RenderWindow> m_window;
  std::unique_ptr<FSM> m_stateMachine;
};



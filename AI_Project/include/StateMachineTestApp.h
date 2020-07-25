#pragma once
#include "BaseApp.h"
class StateMachineTestApp :
  public BaseApp {
  
public:
  int run() override;
private:
  int start() ;

  int mainLoop();

  unsigned int m_screenWidth = 900;
  unsigned int m_screenHeight = 900;
};


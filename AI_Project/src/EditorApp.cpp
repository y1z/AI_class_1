#include <iostream>
#include "EditorApp.h"

namespace fs = std::filesystem;

using std::make_unique;

EditorApp::EditorApp()
  : BaseApp()
{
  m_path = fs::current_path();
}

int 
EditorApp::run(unsigned int screenWidth, 
               unsigned int screenHeight) {
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  return mainLoop();
}

int 
EditorApp::mainLoop() {
  return 0;
}

int 
EditorApp::init() {

  try {
    m_window = make_unique<sf::RenderWindow>();

  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}

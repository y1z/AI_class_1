#include <iostream>
#include "util.h"
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

  if(init() == -1)
  {
    return -1;
  }

  return mainLoop();
}

int 
EditorApp::mainLoop() {



  while (m_window->isOpen())
  {

  }

  return 0;
}

int 
EditorApp::init() {

  try {
    m_window = make_unique<sf::RenderWindow>();

    fs::path temp = m_path.append("resources/test_doc.txt");
    m_file = util::loadFileToString(temp.generic_string());
    if(m_file == "Error")
    {
      return -1;
    }

  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}

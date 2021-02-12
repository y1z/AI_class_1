#include <iostream>
#include "util.h"
#include "EditorApp.h"

namespace fs = std::filesystem;

using std::make_unique;

constexpr static const char* s_pathToTextDefault = "resources/test_doc.txt";

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


  while (m_window->isOpen()) {

    m_timer.StartTiming();
    handleRacers();

    handleInput();

    handleDraw();

    m_timer.EndTiming();
    m_deltaTime = m_timer.GetResultSecondsFloat();

  }

  return 0;
}

int 
EditorApp::init() {

  try {
    m_window = make_unique<sf::RenderWindow>(sf::VideoMode(m_screenWidth, m_screenHeight),
                                             sf::String("final app"),
                                             sf::Style::Default);

    const fs::path temp = fs::path(m_path).append(s_pathToTextDefault);
    m_file = util::loadFileToString(temp.generic_string());
    if (m_file == "Error") {
      return -1;
    }

    GameManager::StartUp(nullptr);

  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}

RESULT_APP_STAGES::E
EditorApp::handleDraw() {
  return RESULT_APP_STAGES::MISSING_IMPL;
}

RESULT_APP_STAGES::E
EditorApp::handleInput() {

  sf::Event event;
  while (m_window->pollEvent(event)) {
    if (sf::Event::Closed == event.type ||
        sf::Keyboard::Escape == event.key.code) {
      m_window->close();
    }

  }

  return RESULT_APP_STAGES::E::NO_ERROR;
}

RESULT_APP_STAGES::E
EditorApp::handleRacers() {

  return RESULT_APP_STAGES::E::MISSING_IMPL;
}

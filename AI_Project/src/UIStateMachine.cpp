#include "UIStateMachine.h"
// states
#include "UIStateWaiting.h"

using std::make_unique;


bool
UIStateMachine::init(const std::vector<UISceneDesc>& descriptor) {
  m_scenes.reserve(descriptor.size());

  for (auto elem : descriptor) {
    m_scenes.emplace_back(UIScene(elem));
  }

  m_states[UI_STATE_NAME::kWAITING] = make_unique<UIStateWaiting>();
  m_states[UI_STATE_NAME::kWAITING]->ptr_scenes = &m_scenes;

  m_currentScene = m_states[UI_STATE_NAME::kWAITING].get();

  for (auto& elem : m_states) {
    elem->ptr_scenes = &m_scenes;
  }

  return true;
}


bool
UIStateMachine::update(const sf::Vector2f& mousePosition,
                       const sf::Mouse::Button accion) {
  UIStateData currentData;
  currentData.mousePosition = mousePosition;
  currentData.mouseAccion = accion;
  currentData.ID = m_currentScene->index;

  return false;
}


void
UIStateMachine::render(sf::RenderWindow* window) {
  auto currentIndex = m_currentScene->index;
  for (auto& elem : m_scenes[currentIndex].m_desc.rectangles) {
    elem.draw(*window);
  }
}




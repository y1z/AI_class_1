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



  m_states[UI_STATE_NAME::kWAITING] = make_unique <UIStateWaiting>();
  m_currentScene = m_states[UI_STATE_NAME::kWAITING].get();

  for (auto& elem : m_states) {
    elem->ptr_scenes = &m_scenes;
  }

  return true;
}

void
UIStateMachine::update(const sf::Vector2f& mousePosition) {}

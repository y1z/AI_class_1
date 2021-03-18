#include "UIStateMachine.h"
#include "BaseApp.h"
#include <cassert>
// states
#include "UIStateWaiting.h"
#include "UIStateChanging.h"

using std::make_unique;


bool
UIStateMachine::init(const std::vector<UISceneDesc>& descriptor,
                     BaseApp* const currentApp) {

  assert(nullptr != currentApp);
  m_scenes.reserve(descriptor.size());

  for (auto& elem : descriptor) {
    m_scenes.emplace_back(std::move(UIScene(elem)));
  }

  m_states[UI_STATE_NAME::kWAITING] = make_unique<UIStateWaiting>();
  m_states[UI_STATE_NAME::kCHANGING] = make_unique<UIStateChanging>();

  m_states[UI_STATE_NAME::kWAITING]->ptr_scenes = &m_scenes;
  m_states[UI_STATE_NAME::kCHANGING]->ptr_scenes = &m_scenes;

  m_states[UI_STATE_NAME::kWAITING]->editor = currentApp;
  m_states[UI_STATE_NAME::kCHANGING]->editor = currentApp;

  m_currentApp = currentApp;

  m_currentScene = m_states[UI_STATE_NAME::kWAITING].get();

  m_currentApp = currentApp;

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
  currentData.sceneIndex = m_currentScene->sceneIndex;

  m_scenes[m_currentScene->sceneIndex].update();

  const auto state = m_currentScene->getCurrentState();
  const auto updatedState = m_currentScene->onUpdate(currentData);

  if (state != updatedState) {
    m_currentScene->onExit(currentData);
    m_currentScene = m_states[updatedState].get();
  }

  return true;
}


void
UIStateMachine::render(sf::RenderWindow* window) {
  const auto currentIndex = m_currentScene->sceneIndex;
  if (-1 != currentIndex) {

    for (auto& elem : m_scenes[currentIndex].m_desc.rectangles) {
      elem.draw(*window);
    }

    for (auto& elem : m_scenes[currentIndex].m_desc.texts) {
      elem.text.draw(window);
    }
  }
}

bool
UIStateMachine::isStateMachineActive() const {
  return !(-1 == m_currentScene->sceneIndex);
}



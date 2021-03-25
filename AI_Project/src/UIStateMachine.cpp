#include "UIStateMachine.h"
#include "BaseApp.h"
#include <cassert>
#include "MouseData.h"
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

  m_states[UI_STATE_NAME::kWAITING]->m_pScenes = &m_scenes;
  m_states[UI_STATE_NAME::kCHANGING]->m_pScenes = &m_scenes;

  m_states[UI_STATE_NAME::kWAITING]->m_pBaseApp = currentApp;
  m_states[UI_STATE_NAME::kCHANGING]->m_pBaseApp = currentApp;

  m_currentApp = currentApp;

  m_currentScene = m_states[UI_STATE_NAME::kWAITING].get();

  m_currentApp = currentApp;

  for (auto& elem : m_states) {
    elem->m_pScenes = &m_scenes;
  }

  return true;
}


bool
UIStateMachine::update(const MouseData& data,
                       const float deltaTime) {
  UIStateData currentData;
  currentData.mouseData = data;
  currentData.sceneIndex = m_currentScene->m_sceneIndex;
  currentData.deltaTime = deltaTime;

  m_scenes[m_currentScene->m_sceneIndex].update();

  const auto updatedState = m_currentScene->onUpdate(currentData);

  if (m_currentScene->getCurrentState() != updatedState) {
    m_currentScene->onExit(currentData);
    m_currentScene = m_states[updatedState].get();
  }

  return true;
}


void
UIStateMachine::render(sf::RenderWindow* window) {
  const auto currentIndex = m_currentScene->m_sceneIndex;
  if (UIScene::NOMORE_SCENES_ID != currentIndex) {
    m_scenes[currentIndex].draw(window);
  }
}

bool
UIStateMachine::isStateMachineActive() const {
  return !(UIScene::NOMORE_SCENES_ID == m_currentScene->m_sceneIndex);
}



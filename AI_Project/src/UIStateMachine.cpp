#include "UIStateMachine.h"
#include "UIStateWaiting.h"


UIStateMachine::UIStateMachine() {
  m_states.fill(nullptr);
}

UIStateMachine::~UIStateMachine()
{
  for (UIState* elemptr : m_states) {
    if (nullptr != elemptr) {
      delete elemptr;
    }
  }

}

bool
UIStateMachine::init(const std::vector<UISceneDescriptor>& descriptor) {
  m_scenes.reserve(descriptor.size());

  for (auto elem : descriptor) {
    m_scenes.emplace_back(UIScene(elem));
  }



  m_states[UI_STATE_NAME::kWAITING] = new UIStateWaiting();
  m_currentScene = m_states[UI_STATE_NAME::kWAITING];


  for (auto state : m_states) {
    state->ptr_scenes = &m_scenes;
  }

  return true;
}

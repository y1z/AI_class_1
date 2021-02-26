#pragma once
#include <vector>
#include <array>
#include <UIScene.h>
#include "UIState.h"



class UIStateMachine
{
public:
  UIStateMachine();
  ~UIStateMachine();

  bool
  init(const std::vector<UISceneDescriptor>& descriptor );

  UIState* m_currentScene;
  std::array<UIState*, UI_STATE_NAME::E::kNumStates> m_states;
  std::vector<UIScene> m_scenes;
};


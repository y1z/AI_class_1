#pragma once
#include <vector>
#include <array>
#include <memory>

#include "UIScene.h"
#include "UIState.h"

class BaseApp;
class MouseData;


/**
 * @brief controls the UI.
 */
class UIStateMachine
{
public:
  UIStateMachine() = default;
  UIStateMachine(const UIStateMachine& other) = delete;
  UIStateMachine(UIStateMachine&& other)noexcept = default;

  ~UIStateMachine() = default;

  UIStateMachine&
  operator=(const UIStateMachine& other) = delete;

  UIStateMachine&
  operator=(UIStateMachine&& other)noexcept = default;


  /**
   * @brief Starts up the state machine
   */
  bool
  init(const std::vector<UISceneDesc>& descriptor,
       BaseApp* const currentApp);

  /**
   * @brief Starts up the state machine
   */
  bool
  update(const MouseData& data,
         const float deltaTime);

  void
  render(sf::RenderWindow* window);

  bool
  isStateMachineActive()const;

  UIState* m_currentScene;
  BaseApp* m_currentApp;
  std::vector<UIScene> m_scenes;
  std::array<std::unique_ptr<UIState>, UI_STATE_NAME::E::kNumStates> m_states;
};


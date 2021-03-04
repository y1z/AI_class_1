#pragma once
#include <vector>
#include <array>
#include <memory>

#include "UIScene.h"
#include "UIState.h"



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
  init(const std::vector<UISceneDesc>& descriptor);

  /**
   * @brief Starts up the state machine
   */
  bool
  update(const sf::Vector2f& mousePosition,
         const sf::Mouse::Button accion);

  void
  render(sf::RenderWindow* window);

  bool
  isStateMachineActive()const;

  UIState* m_currentScene;
  std::vector<UIScene> m_scenes;
  std::array<std::unique_ptr<UIState>, UI_STATE_NAME::E::kNumStates> m_states;
};


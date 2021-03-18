#pragma once
#include <cstdint>
#include "UIScene.h"

namespace UI_STATE_NAME {

enum E : size_t {
  kWAITING = 0,
  kCHANGING = 1,
  kNumStates
};

}

/**
 * The data that the state needs for work.
 */
struct UIStateData
{
  UIStateData() = default;
  UIStateData(const sf::Vector2f& _mousePosition,
              const float _deltaTime,
              int32_t _sceneIndex,
              int32_t _lastSceneID,
              int32_t _mouseAccion)
    : mousePosition(_mousePosition),
      deltaTime(_deltaTime),
      sceneIndex(_sceneIndex),
      lastSceneID(_lastSceneID),
      mouseAccion(_mouseAccion)
  {}

  /**
   * Where the mouse is located on the screen.
   */
  sf::Vector2f mousePosition;
  /**
   * The since the last update.
   */
  float deltaTime;
  /** keeps track of which sate we are in. */
  int32_t sceneIndex;
  int32_t lastSceneID;
  int32_t mouseAccion;
};


/**
 * Is a interface for all UI states.
 */
struct UIState
{
  UIState() = default;
  virtual ~UIState() = default;

  virtual UI_STATE_NAME::E
  onUpdate(UIStateData& mousePos) = 0;

  virtual UI_STATE_NAME::E
  onExit(UIStateData& mousePos) = 0;

  virtual UI_STATE_NAME::E
  getCurrentState()const = 0;

  std::vector<UIScene>* ptr_scenes;
  BaseApp* editor = nullptr;
  int32_t sceneIndex = 0;
};


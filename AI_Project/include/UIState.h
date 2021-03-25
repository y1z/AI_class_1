#pragma once
#include <cstdint>
#include "UIScene.h"
#include "MouseData.h"

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
  UIStateData(const MouseData& _mouseData,
              const float _deltaTime,
              int32_t _sceneIndex,
              int32_t _lastSceneID)
    :
    mouseData(_mouseData),
    deltaTime(_deltaTime),
    sceneIndex(_sceneIndex),
    lastSceneIndex(_lastSceneID)
  {}


  /**
   * Keeps track of relevant data related with the mouse.
   */
  MouseData mouseData;

  /**
   * The since the last update.
   */
  float deltaTime;

  /** keeps track of which sate we are in. */
  int32_t sceneIndex;


  /** keeps track of the last state we were in. */
  int32_t lastSceneIndex;
};


/**
 * Is a interface for all UI states.
 */
struct UIState
{
  UIState() = default;
  virtual ~UIState() = default;

  /**
   * Controls what the state does every update.
   */
  virtual UI_STATE_NAME::E
  onUpdate(UIStateData& mousePos) = 0;

  /**
   * Controls what happens when the state.
   */
  virtual UI_STATE_NAME::E
  onExit(UIStateData& mousePos) = 0;

  /**
   * Controls what the state does every update.
   */
  virtual UI_STATE_NAME::E
  getCurrentState()const = 0;

  std::vector<UIScene>* ptr_scenes;
  BaseApp* editor = nullptr;
  int32_t sceneIndex = 0;
};


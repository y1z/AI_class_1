#pragma once
#include <cstdint>
#include "UIScene.h"

namespace UI_STATE_NAME {

enum E : size_t {
  kStop,
  kWAITING = 0,
  kCHANGING = 1,
  kNumStates
};

}

struct UIStateData
{
  sf::Vector2f mousePosition;
  /** keeps track of which sate we are in*/
  int32_t ID;
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


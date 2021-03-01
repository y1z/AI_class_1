#pragma once
#include <cstdint>
#include "UIScene.h"

namespace UI_STATE_NAME {
enum E : size_t
{
  kWAITING = 0,
  kCHANGING,
  kNumStates
};

}

struct UIStateData
{

  /** keeps track of which sate we are in*/
  sf::Vector2i currentStateID;
  sf::Vector2i lastIndexID;
};


/**
 * Is a interface for all UI states.
 */
struct UIState
{
  UIState() = default;
  virtual ~UIState() = default;

  virtual UI_STATE_NAME::E
  onUpdate(const sf::Vector2f& mousePos,
           int32 mouseButtonCode) = 0;

  virtual UI_STATE_NAME::E
  onExit(const sf::Vector2f& mousePos,
         int32 mouseButtonCode) = 0;

  virtual UI_STATE_NAME::E
  getCurrentState()const = 0;


  sf::Vector2i index = sf::Vector2i(0, 0);
  std::vector<UIScene>* ptr_scenes;
};


#pragma once
#include "UIState.h"



/**
 * What the UI does when waiting for user input.
 */
class UIStateWaiting final : public UIState
{
public:

  UIStateWaiting() = default;
  ~UIStateWaiting() = default;

  UI_STATE_NAME::E
  onUpdate(const UIStateData sceneData) override;

  UI_STATE_NAME::E
  onExit(const UIStateData sceneData) override;

  UI_STATE_NAME::E
  getCurrentState()const override;

};


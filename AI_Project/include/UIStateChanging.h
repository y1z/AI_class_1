#pragma once
#include "UIState.h"



class UIStateChanging final : public UIState
{
public:
  UIStateChanging() = default;
  ~UIStateChanging() = default;

  UI_STATE_NAME::E
  onUpdate(UIStateData& mousePos) override;

  UI_STATE_NAME::E
  onExit(UIStateData& mousePos) override;

  UI_STATE_NAME::E
  getCurrentState()const override;


};






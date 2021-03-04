#pragma once
#include "UIState.h"



class UIStateChanging final : public UIState
{
public:
  UIStateChanging() = default;
  ~UIStateChanging() = default;

  virtual UI_STATE_NAME::E
  onUpdate(UIStateData& mousePos) override;

  virtual UI_STATE_NAME::E
  onExit(UIStateData& mousePos) override;

  virtual UI_STATE_NAME::E
  getCurrentState()const override;


};






#pragma once
#include "UIState.h"



class UIStateChanging : public UIState
{
public:
  UIStateChanging() = default;
  ~UIStateChanging() = default;

  virtual UI_STATE_NAME::E
  onUpdate(const UIStateData mousePos) override;

  virtual UI_STATE_NAME::E
  onExit(const UIStateData mousePos) override;

  virtual UI_STATE_NAME::E
  getCurrentState()const override;


};






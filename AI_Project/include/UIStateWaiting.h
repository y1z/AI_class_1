#pragma once
#include "UIState.h"



class UIStateWaiting final : public UIState
{
public:

  UIStateWaiting () = default;
  ~UIStateWaiting () = default;

  UI_STATE_NAME::E
  onUpdate(const sf::Vector2f& mousePos,
           int32 mouseButtonCode) override;

  UI_STATE_NAME::E
  onExit(const sf::Vector2f& mousePos,
         int32 mouseButtonCode) override;

  UI_STATE_NAME::E
  getCurrentState()const override;

};


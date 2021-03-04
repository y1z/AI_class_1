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
  onUpdate(UIStateData& sceneData) override;

  void
  executeCallBack(int32 callbackIndex, const  UISceneDesc& scene);

  UI_STATE_NAME::E
  onExit(UIStateData& sceneData) override;

  UI_STATE_NAME::E
  getCurrentState()const override;

};


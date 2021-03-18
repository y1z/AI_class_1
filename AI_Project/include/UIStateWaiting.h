#pragma once
#include "UIState.h"

#include <optional>



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

  std::optional<int>
  executeCallBack(int32 callbackIndex, const  UISceneDesc& scene);

  UI_STATE_NAME::E
  onExit(UIStateData& sceneData) override;

  UI_STATE_NAME::E
  getCurrentState()const override;

  float m_timeSinceInput = 0.0f;
};


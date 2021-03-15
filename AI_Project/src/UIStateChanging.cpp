#include "UIStateChanging.h"

UI_STATE_NAME::E
UIStateChanging::onUpdate(UIStateData& stateData) {
  static_cast<void>(stateData);

  return UI_STATE_NAME::E();
}

UI_STATE_NAME::E
UIStateChanging::onExit(UIStateData& stateData) {
  static_cast<void>(stateData);
  return UI_STATE_NAME::E::kWAITING;
}

UI_STATE_NAME::E
UIStateChanging::getCurrentState() const {
  return UI_STATE_NAME::E::kCHANGING;
}

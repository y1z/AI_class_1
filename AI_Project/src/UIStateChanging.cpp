#include "UIStateChanging.h"

UI_STATE_NAME::E
UIStateChanging::onUpdate(UIStateData& mousePos) {

    return UI_STATE_NAME::E();
}

UI_STATE_NAME::E
UIStateChanging::onExit(UIStateData& mousePos) {
  return UI_STATE_NAME::E::kWAITING;
}

UI_STATE_NAME::E
UIStateChanging::getCurrentState() const {
  return UI_STATE_NAME::E::kCHANGING;
}

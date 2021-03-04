#include "UIStateChanging.h"

UI_STATE_NAME::E
UIStateChanging::onUpdate(const UIStateData mousePos) {
    return UI_STATE_NAME::E();
}

UI_STATE_NAME::E
UIStateChanging::onExit(const UIStateData mousePos) {
  return UI_STATE_NAME::E::kWAITING;
}

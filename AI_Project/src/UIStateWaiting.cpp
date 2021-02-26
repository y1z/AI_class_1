#include "UIStateWaiting.h"

UI_STATE_NAME::E
UIStateWaiting::onUpdate(const sf::Vector2f& mousePos,
                         int32 mouseButtonCode) {

  if (ptr_scenes->at(index.x).m_desc.rectangles[index.y].isInsideRect(mousePos)) {
    return UI_STATE_NAME::kCHANGING;
  }

  return UI_STATE_NAME::E::kWAITING;
}

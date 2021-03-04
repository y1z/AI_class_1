#include <cassert>
#include "UIStateWaiting.h"



UI_STATE_NAME::E
UIStateWaiting::onUpdate(const UIStateData sceneData) {
  assert(nullptr != ptr_scenes);
  std::vector<UiRectangle>& UISceneElements = ptr_scenes->at(index).m_desc.rectangles;
  UISceneDesc& scene = ptr_scenes->at(index).m_desc;

  size_t i = 0;
  for (const auto& elem : UISceneElements) {

    const bool isIsideUI = elem.isInsideRect(sceneData.mousePosition);
    if (isIsideUI && sf::Mouse::Left == sceneData.mouseAccion) {
      index = scene.associatedScenes.at(i);
      return UI_STATE_NAME::E::kCHANGING;
    }

    ++i;
  }

  return UI_STATE_NAME::E::kWAITING;
}


UI_STATE_NAME::E
UIStateWaiting::onExit(const UIStateData sceneData) {
  return UI_STATE_NAME::E();
}

UI_STATE_NAME::E
UIStateWaiting::getCurrentState() const {
  return UI_STATE_NAME::E::kWAITING;
}

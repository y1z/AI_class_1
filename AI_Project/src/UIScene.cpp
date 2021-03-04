#include "UIScene.h"

UIScene::UIScene(const UISceneDesc& descriptor)
  :m_desc(descriptor) {}

void
UISceneDesc::AddElement(const UiRectangle& _rectangle,
                        const int32_t _associatedScene,
                        const UICallbackFunction& _callback) {

  rectangles.emplace_back(_rectangle);
  associatedScenes.emplace_back(_associatedScene);
  callbackFunctions.emplace_back(_callback);
}


#include "UIScene.h"

UIScene::UIScene(const UISceneDesc& descriptor)
  :m_desc(descriptor) {}

void
UISceneDesc::AddElement(const UIRectangle& _rectangle,
                        const int32_t _associatedScene,
                        const UICallbackFunction& _callback) {

  rectangles.emplace_back(_rectangle);
  associatedScenes.emplace_back(_associatedScene);
  callbackFunctions.emplace_back(_callback);
}

void
UISceneDesc::AddElement(const UIRectangle& _rectangle,
                        const int32_t _associatedScene,
                        const UICallbackFunction& _callback,
                        const UITextDescriptor& _textDesc) {
  rectangles.emplace_back(_rectangle);
  associatedScenes.emplace_back(_associatedScene);
  callbackFunctions.emplace_back(_callback);
  {
    TextElement newTextElement;
    newTextElement.text.init(_textDesc);
    newTextElement.index = static_cast<uint64>(rectangles.size() - 1);
    texts.push_back(std::move(newTextElement));
  }

}


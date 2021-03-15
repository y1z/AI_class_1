#include "UIScene.h"

UIScene::UIScene(const UISceneDesc& descriptor)
  :m_desc(descriptor) {}

UIScene::UIScene(UISceneDesc&& descriptor)
  :m_desc(std::move(descriptor))
{}

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
  UIText resultingText;
  resultingText.init(_textDesc);

  AddElement(_rectangle, _associatedScene, _callback, std::move(resultingText));

}

void
UISceneDesc::AddElement(const UIRectangle& _rectangle,
                        const int32_t _associatedScene,
                        const UICallbackFunction& _callback,
                        UIText&& _text) {

  rectangles.emplace_back(_rectangle);
  associatedScenes.emplace_back(_associatedScene);
  callbackFunctions.emplace_back(_callback);
  {
    TextElement newTextElement;
    newTextElement.text = std::move(_text);
    newTextElement.index = static_cast<uint64>(rectangles.size() - 1);
    texts.emplace_back(std::move(newTextElement));
  }

}


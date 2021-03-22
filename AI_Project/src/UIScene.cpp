#include "UIScene.h"
#include <cassert>

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
                        const UIText& _text) {
  UIText copy(_text);

  AddElement(_rectangle, _associatedScene, _callback, std::move(copy));
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
    newTextElement.text.takeResources(std::move(_text));
    newTextElement.index = static_cast<uint64>(rectangles.size() - 1);
    newTextElement.text.attachToReactangle(&rectangles[newTextElement.index]);
    texts.emplace_back(std::move(newTextElement));
  }

}



UIScene::UIScene(const UISceneDesc& descriptor)
  : m_desc(descriptor) {}

UIScene::UIScene(UISceneDesc&& descriptor)
  : m_desc(std::move(descriptor)) {}

void
UIScene::update() {
  for (auto& elem : m_desc.texts) {
    if (UISceneDesc::TextElement::INVALID_INDEX != elem.index) {
      auto& rectangles = m_desc.rectangles;
      auto& refToRec = rectangles[elem.index];
      elem.text.attachToReactangle(&refToRec);
      elem.text.makeTextFitSimple(refToRec.m_rect.getGlobalBounds());
    }
  }

}


void
UIScene::draw(sf::RenderTarget* target)const {
  assert(nullptr != target);
  for (const auto& elem : m_desc.rectangles) {
    elem.draw(*target);
  }

  for (const auto& elem : m_desc.texts) {
    elem.text.draw(target);
  }
}


UIRectangle
UIScene::copyAndModifyFromTemplate(const UIRectangle& templateRectangle,
                                   const std::optional<sf::Color> color,
                                   const std::optional<Vec2> howMuchToMove,
                                   const std::optional<Vec2> newSize) {
  UIRectangle result(templateRectangle);

  if (color.has_value()) {
    result.m_rect.setFillColor(*color);
  }

  if (howMuchToMove.has_value()) {
    const auto position = result.m_rect.getPosition();
    result.m_rect.setPosition(sf::Vector2f(position.x + (*howMuchToMove).x,
                                           position.y + (*howMuchToMove).y));
  }

  if (newSize.has_value()) {
    const auto valNewSize = *newSize;
    result.m_rect.setSize(sf::Vector2f(valNewSize.x, valNewSize.y));
  }

  return result;
}



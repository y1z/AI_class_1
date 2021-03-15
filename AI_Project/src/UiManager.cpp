#include "UiManager.h"

#include <iostream>


bool
UiManager::init(const std::vector< UIRectangleDesc >& descriptors) {
  m_rectangles.reserve(descriptors.size());
  try {
    for (const auto& des : descriptors) {
      addRectangle(des);
    }

  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n\n";
  }


  return true;
}

void
UiManager::addRectangle(const UIRectangleDesc& desc) {
  m_rectangles.emplace_back(UIRectangle(desc));
}

void
UiManager::addRectangle(const UIRectangleDesc& rectangleDesc,
                        const UITextDescriptor& textDesc) {
  addRectangle(rectangleDesc);
  const auto index = static_cast<uint64>(m_rectangles.size() - 1);
  const auto rect = &m_rectangles[index];
  {
    UIText addedText;
    addedText.init(textDesc);
    addedText.attachToReactangle(rect);
    m_texts.push_back(TextElement{ index,std::move(addedText) });
  }
}

void
UiManager::resizeAllRectangle(const sf::Vector2f& newSize) {
  for (auto& rect : m_rectangles) {
    rect.resizeRectangle(newSize);
  }

}

UIRectangle&
UiManager::getRectangle(const uint64 index) {
  return m_rectangles.at(index);
}

UIText&
UiManager::getText(const uint64 index) {
  return m_texts[index].text;
}

uint64
UiManager::getRectangleCount() const {
  return m_rectangles.size();
}

uint64
UiManager::getTextsCount() const {
  return m_texts.size();
}


void
UiManager::draw(sf::RenderTarget& target) {
  for (const auto& rect : m_rectangles) {
    rect.draw(target);
  }

}

UiManager::RectangleContainer::iterator
UiManager::begin() {
  return m_rectangles.begin();
}

UiManager::RectangleContainer::iterator
UiManager::end() {
  return m_rectangles.end();
}




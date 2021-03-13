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
UiManager::resizeAllRectangle(const sf::Vector2f& newSize) {
  for (auto& rect : m_rectangles) {
    rect.resizeRectangle(newSize);
  }

}

UIRectangle&
UiManager::getRectangle(const uint32 index) {
  return m_rectangles.at(index);
}

uint32
UiManager::getRectangleCount() const {
  return m_rectangles.size();
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




#pragma once
#include <cstdint>
#include <vector>
#include "UiRectangle.h"

struct UISceneDescriptor
{
  std::vector<UiRectangle> rectangles;
  sf::Vector2i ID;
  sf::Vector2i nextScene;

  constexpr bool
  operator<(const UISceneDescriptor& other)const {
    if (ID.x == other.ID.x) {
      return ID.y < other.ID.y;
    }

    return ID.x < other.ID.x;
  }

  constexpr bool
  operator>(const UISceneDescriptor& other)const {
    if (ID.x == other.ID.x) {
      return ID.y > other.ID.y;
    }

    return ID.x > other.ID.x;
  }

  constexpr bool
  operator==(const UISceneDescriptor& other)const {
    return ID.x > other.ID.x && ID.y > other.ID.y;
  }
};


/**
 * Controls whats a scene has.
 */
class UIScene {
public:
  explicit UIScene(const UISceneDescriptor& descriptor);

  constexpr bool
  operator<(const UIScene& other)const {
    return m_desc < other.m_desc;
  }


  constexpr bool
  operator>(const UIScene& other)const {
    return m_desc > other.m_desc;
  }


  constexpr bool
  operator==(const UIScene& other)const {
    return m_desc == other.m_desc;
  }

  UISceneDescriptor m_desc;
  sf::Vector2i nextScene;
};


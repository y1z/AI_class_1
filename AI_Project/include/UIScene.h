#pragma once
#include <cstdint>
#include <vector>
#include "UiRectangle.h"


/**
 * controls
 */
struct UISceneDesc
{
  std::vector<UiRectangle> rectangles;/**< The visual representation*/
  std::vector<int32_t> associatedScenes;
  int32_t ID;

  constexpr bool
  operator<(const UISceneDesc& other)const {
    return ID < other.ID;
  }

  constexpr bool
  operator>(const UISceneDesc& other)const {

    return ID > other.ID;
  }

  constexpr bool
  operator==(const UISceneDesc& other)const {
    return ID == other.ID;
  }
};


/**
 * Controls whats a scene has.
 */
class UIScene {
public:
  explicit UIScene(const UISceneDesc& descriptor);

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

  UISceneDesc m_desc;
};


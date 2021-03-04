#pragma once
#include <cstdint>
#include <vector>
#include "UiRectangle.h"


/**
 * Contains the data for creating a scene.
 */
struct UISceneDesc
{
  std::vector<UiRectangle> rectangles;/**< The visual representation. */
  std::vector<int32_t> associatedScenes;/**< The connections between scenes. */
  int32_t ID; /**< Used to identify the scenes. */

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

  constexpr bool
  operator <= (const UISceneDesc& other)const {
    return !(this->operator>(other));
  }

  constexpr bool
  operator >= (const UISceneDesc& other)const {
    return !(this->operator<(other));
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


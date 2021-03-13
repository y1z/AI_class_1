#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <variant>
#include <filesystem>
#include "UiRectangle.h"
#include "BaseApp.h"


/**
 * Contains the data for creating a scene.
 */
struct UISceneDesc
{
  /** The types of function that the struct can accept.*/
  using UICallbackFunction =
    std::variant< std::function<void(void)>,
                  std::function<int(void)>,
                  std::function<std::filesystem::path (BaseApp*) > >;


  std::vector<UIRectangle> rectangles;/**< The visual representation. */
  std::vector<int32_t> associatedScenes;/**< The connections between scenes. */
  std::vector<UICallbackFunction> callbackFunctions;
  int32_t ID; /**< Used to identify the scenes. */


  void
  AddElement(const UIRectangle& _rectangle,
             const int32_t _associatedScene,
             const UICallbackFunction& _callback = []() {});

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


#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <variant>
#include <filesystem>
#include "UiRectangle.h"

#include "UIText.h"
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

  struct TextElement {
    UIText text;
    uint64 index;
  };


  std::vector<UIRectangle> rectangles;/**< The visual representation of rectangles. */
  std::vector<int32_t> associatedScenes;/**< The connections between scenes. */
  std::vector<UICallbackFunction> callbackFunctions;
  std::vector<TextElement> texts; /**< The visual representation of text.*/
  int32_t ID; /**< Used to identify the scenes. */


  void
  AddElement(const UIRectangle& _rectangle,
             const int32_t _associatedScene,
             const UICallbackFunction& _callback = []() {});


  void
  AddElement(const UIRectangle& _rectangle,
             const int32_t _associatedScene,
             const UICallbackFunction& _callback,
             const UITextDescriptor& _textDesc);


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


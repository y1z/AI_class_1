#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <variant>
#include <filesystem>
#include "UiRectangle.h"

#include "UIText.h"
#include "BaseApp.h"


struct UISceneDesc
{
  /** The types of function that the struct can accept.*/
  using UICallbackFunction =
    std::variant< std::function<void(void)>,
                  std::function<int(void)>,
                  std::function<std::filesystem::path (BaseApp*) > >;

  struct TextElement {
    TextElement() = default;
    TextElement(TextElement&& other) noexcept = default;

    TextElement(const TextElement& other) = default;

    TextElement&
    operator=(TextElement&& other) noexcept = default;

    TextElement&
    operator=(const TextElement& other) = delete;
    //TextElement() = default;
    //TextElement(TextElement&& other) noexcept {
    //  text = std::move(other.text);
    //}
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


  void
  AddElement(const UIRectangle& _rectangle,
             const int32_t _associatedScene,
             const UICallbackFunction& _callback,
             const UIText& _text);


  void
  AddElement(const UIRectangle& _rectangle,
             const int32_t _associatedScene,
             const UICallbackFunction& _callback,
             UIText&& _text);


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
 * Contains the data for creating a scene.
 */


/**
 * Controls whats a scene has.
 */
class UIScene
{
public:
  explicit UIScene(const UISceneDesc& descriptor);

  explicit UIScene(UISceneDesc&& descriptor);


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

  void
  update();

  void
  draw(sf::RenderTarget* target)const;
 private:

 public:
  UISceneDesc m_desc;
};



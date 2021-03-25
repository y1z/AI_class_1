#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <variant>
#include <filesystem>
#include "UiRectangle.h"
#include <optional>

#include "UIText.h"
#include "BaseApp.h"


/**
 * Contains the data for creating a scene.
 */
struct UISceneDesc
{

  /**
   * Typedefs
   */
  using AppFuncReturnFilePath = std::function<std::filesystem::path(BaseApp*)>;
  using AppFuncReturnInt = std::function<int(BaseApp*)>;

  /** The types of function that the struct can accept.*/
  using UICallbackFunction =
    std::variant< std::function<void(void)>,
                  std::function<int(void)>,
                  AppFuncReturnFilePath ,
                  AppFuncReturnInt >;

  using UICallBackContainer = std::vector< UICallbackFunction >;

  struct TextElement {
    TextElement() = default;
    TextElement(TextElement&& other) noexcept = default;

    TextElement(const TextElement& other) = default;

    TextElement&
    operator=(TextElement&& other) noexcept = default;

    TextElement&
    operator=(const TextElement& other) = delete;

    constexpr static const uint64 INVALID_INDEX = std::numeric_limits<uint64>::max();

    UIText text;
    uint64 index;
  };



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


  std::vector<UIRectangle> rectangles;/**< The visual representation of rectangles. */
  std::vector<int32_t> associatedScenes;/**< The connections between scenes. */
  std::vector<UICallbackFunction> callbackFunctions;
  std::vector<TextElement> texts; /**< The visual representation of text.*/
  int32_t ID; /**< Used to identify the scenes. */
};


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

  constexpr bool
  operator<=(const UIScene& other)const {
    return m_desc.operator<=(other.m_desc);
  }


  constexpr bool
  operator>=(const UIScene& other)const {
    return m_desc.operator>=(other.m_desc);
  }


  /**
   * updates the Scene.
   */
  void
  update();

  /**
   * draws the scene
   */
  void
  draw(sf::RenderTarget* target)const;

  /**
   * Create a new UIRectangle from a already created template
   */
  static UIRectangle
  copyAndModifyFromTemplate(const UIRectangle& templateRectangle,
                            const std::optional<sf::Color> color = std::nullopt,
                            const std::optional<Vec2> howMuchToMove = std::nullopt,
                            const std::optional<Vec2> newSize = std::nullopt);


   /**
    * Used to indicate no more scenes are going to load.
    */
  constexpr static int32 NOMORE_SCENES_ID = -1;
 private:


 public:
  UISceneDesc m_desc;
};



#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <memory>
#include <string_view>


/**
 * forward declaration's
 */
struct UITextDescriptor;
class UIRectangle;

namespace TEXT_ALIGNMENT {
enum E
{
  leftAlign,
  centerAlign,
  DEFAULT = leftAlign,
  };
}


/**
 * The representation text with the UI.
 */
class UIText {
 public:

  UIText() = default;
  UIText(UIText&& other) noexcept;
  UIText(const UIText& other);

  ~UIText() = default;

  UIText&
  operator=(UIText&& other) noexcept;

  UIText&
  operator=(const UIText& other);

  /**
   * initializes the UIText.
   */
  bool
  init(const UITextDescriptor& descriptor);

  sf::Vector2f
  getPosition()const;

  sf::Color
  getFillColor()const;

  sf::Color
  getOuterColor()const;

  unsigned int
  getCharacterSize()const;

  void
  setPosition(const sf::Vector2f& position);

  void
  setFillColor(const sf::Color color);

  void
  setOuterColor(const sf::Color color);

  void
  setCharacterSize(unsigned int newSize)const;

  void
  setString(const std::string_view newString);

  /**
   * Modify the text so it can fit inside the constraints in global space.
   *
   * @note This algorithm only care if the text fits in the horizontal portion of constraints.
   */
  bool
  makeTextFitSimple(const sf::FloatRect& constraints);

 public:
  /**
   * Connects the text to a UIRectangle which mean the text will follow rectangle.
   */
  void
  attachToReactangle(UIRectangle* pRect)const;


  /**
   * Make the text no-longer be attached to the UIRectangle
   * @NOTE : The text will stay in the same place after this function call
   * use other function for modifying the position of the text.
   */
  void
  unattachFromReactangle();

  /**
   * Draws the text
   */
  void
  draw(sf::RenderTarget* target)const;

  /**
   * Updates the text ( changes the text, moves with a UIRectangle if needed etc..)
   */
  void
  update();


  /**
   * Makes a copy of another instance UIText.
   */
  UIText&
  copy(const UIText& other);

  /**
   * Controls the string to be displayed on UIText
   * @Note changes to this will only be seen after calling the update function.
   */
  sf::String m_textString = { "       " };

 private:

  /**
   * creates the resources
   */
  bool
  internalInit();

  std::unique_ptr<sf::Text> m_text = nullptr;
  std::shared_ptr<sf::Font> m_font = nullptr;
  std::shared_ptr<sf::FileInputStream> m_fileStream = nullptr;
  mutable UIRectangle* m_rectPointer = nullptr;
};


/**
 * Used for initializing a UIText object.
 */
struct UITextDescriptor
{
  sf::String textString = sf::String("      ");
  std::string_view pathToFont;
  sf::Vector2f textPosition = sf::Vector2f(0.0f, 0.0f);
  sf::Color textFillColor = sf::Color(255u, 255u, 255u);
  sf::Color texOuterColor = sf::Color(255u, 255u, 255u);
  unsigned int textSize = 30u;
};




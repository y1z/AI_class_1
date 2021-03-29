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
  enum struct E : uint32_t {
    leftAlign = 0u,
    centerAlign,
    DEFAULT = leftAlign,
  };
}


/**
 * The representation text with the UI.
 */
class UIText
{
public:

  UIText() = default;
  UIText(UIText&& other) noexcept;
  UIText(const UIText& other);

  ~UIText() = default;

  UIText&
  operator=(UIText&& other) noexcept = default;

  UIText&
  operator=(const UIText& other) = default;

  /**
   * initializes the UIText.
   */
  bool
  init(const UITextDescriptor& descriptor);

  /**
   * @returns
   *  The position of the text.
   */
  sf::Vector2f
  getPosition()const;


  /**
   * @returns
   *  The color used by the filling of the text.
   */
  sf::Color
  getFillColor()const;


  /**
   * @returns
   *  The color used by the outline of the text.
   */
  sf::Color
  getOuterColor()const;

  /**
   * @returns
   *  The size of the individual characters.
   */
  unsigned int
  getCharacterSize()const;

  /**
   * Controls the position of the text.
   */
  void
  setPosition(const sf::Vector2f& position);

  /**
   * The color that fills the text.
   */
  void
  setFillColor(const sf::Color color);

  /**
   * Set the color used for the outline of the text.
   */
  void
  setOuterColor(const sf::Color color);


  /**
   * Set the size of the individual characters.
   */
  void
  setCharacterSize(unsigned int newSize);

  /**
   * Set if the text is regular, italicized or bold.
   */
  void
  setTextStyle(sf::Text::Style newStyle);

  /**
   * Controls the alignment of the text with attached to a rectangle.
   */
  void
  setAlignment(const TEXT_ALIGNMENT::E alignment);

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
   * Takes the resources from another UIText
   * @NOTE The UIText object that passed in will be in a INVALID state pleas ignore it after
   * calling this function.
   */
  UIText&
  takeResources(UIText&& other) noexcept;

  /**
   * Controls the string to be displayed on UIText
   * @Note changes to this will only be seen after calling the update function.
   */
  sf::String m_textString = { "       " };

 private:
  void
  alignText()const;

   /**
    * @reutrns
    *  A pair the first argument returns true if the text fits inside the constraints
    *  the second argument return the index of the character that outside the constraints.
    */
  std::pair<bool, uint64_t>
  isTextInsideHorizontalContraints(const sf::FloatRect& constraints)const;

  /**
   * creates the resources
   */
  bool
  internalInit();

  std::unique_ptr<sf::Text> m_text = nullptr;
  std::shared_ptr<sf::Font> m_font = nullptr;
  std::shared_ptr<sf::FileInputStream> m_fileStream = nullptr;
  mutable UIRectangle* m_rectPointer = nullptr;
  sf::Color m_fillColor = sf::Color::Black;
  sf::Color m_outerColor = sf::Color::White;
  unsigned int m_textSize = 30u;
  sf::Text::Style m_textStyle = sf::Text::Style::Regular;
  TEXT_ALIGNMENT::E m_alignment = TEXT_ALIGNMENT::E::DEFAULT;
};


/**
 * Used for initializing a UIText object.
 */
struct UITextDescriptor
{
  sf::String textString = sf::String("      ");/**< Controls the characters of the string*/
  std::string_view pathToFont;/**< Controls which font to load. */
  sf::Vector2f textPosition = sf::Vector2f(0.0f, 0.0f); /**< Controls where the text will be . */
  /**
   * Used for creating a copy from other UIText object.(just keep this a nullptr if you don't
   * what to make a copy.
   */
  UIText* ptrCopyText = nullptr;
  sf::Color textFillColor = sf::Color(255u, 255u, 255u, 255u);
  sf::Color textOuterColor = sf::Color(255u, 255u, 255u, 255u);
  unsigned int textSize = 30u;
  float outlineTextSize = 0.0f;
  sf::Text::Style textStyle = sf::Text::Style::Regular;
  TEXT_ALIGNMENT::E alignment = TEXT_ALIGNMENT::E::DEFAULT;
};




#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <memory>
#include <string_view>


/**
 * forward declaration's
 */
struct UITextDescriptor;
//class UIRectangle;

/**
 * The representation text with the UI.
 */
class UIText {
 public:

  /**
   * initializes the UIText.
   */
  bool
  init(const UITextDescriptor& descriptor);

  sf::Vector2f
  getPosition()const;

  sf::Color
  getColor()const;

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

  void
  draw(sf::RenderTarget* target)const;

  UIText&
  copy(const UIText& other);


 private:

  /**
   * creates the resources
   */
  bool
  internalInit();

  sf::String m_textString = { "       " };
  std::unique_ptr<sf::Text> m_text = nullptr;
  std::shared_ptr<sf::Font> m_font = nullptr;
  std::shared_ptr<sf::FileInputStream> m_fileStream = nullptr;
};


/**
 * Used for initializing a UIText object.
 */
struct UITextDescriptor
{
  std::string_view pathToFont;
  sf::Vector2f textPosition = sf::Vector2f(0.0f, 0.0f);
  sf::Color textFillColor = sf::Color(128u, 128u, 128u);
  sf::Color texOuterColor = sf::Color(128u, 128u, 128u);
  unsigned int textSize = 30u;
};




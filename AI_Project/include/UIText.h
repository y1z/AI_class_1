#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>



/**
 * The representation text with the UI.
 */
class UIText {
 public:



 private:
  std::unique_ptr<sf::Text> m_text;
};


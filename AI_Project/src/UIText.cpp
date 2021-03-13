#include "UIText.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

using std::make_shared;
using std::make_unique;

constexpr static std::string_view s_formatsForFonts = "|.ttf|.eot|.otf|.pfb|.pcf|";

bool
UIText::init(const UITextDescriptor& descriptor) {

  if (nullptr != m_fileStream && nullptr != m_font) {
    return false;
  }

  const bool createdResources = internalInit();
  if (createdResources) {
    /// The supported font formats are: TrueType, Type 1, CFF,
    /// OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
    const bool canLoadStream = m_fileStream->open(descriptor.pathToFont.data());
    const bool hasLoadedFront = m_font->loadFromStream(*m_fileStream);
    if (hasLoadedFront) {
      m_text->setFont(*m_font);
      m_text->setFillColor(descriptor.textFillColor);
      m_text->setCharacterSize(descriptor.textSize);
      m_text->setPosition(descriptor.textPosition);
      m_text->setString(m_textString);
    }
    return canLoadStream && hasLoadedFront;
  }

  return false;
}

sf::Vector2f
UIText::getPosition() const {
  return m_text->getPosition();
}

sf::Color
UIText::getColor() const {
  return m_text->getFillColor();
}

unsigned int
UIText::getCharacterSize() const {
  return m_text->getCharacterSize();
}

void
UIText::setPosition(const sf::Vector2f& position) {
  m_text->setPosition(position);
}

void
UIText::setFillColor(const sf::Color color) {
  m_text->setFillColor(color);
}

void
UIText::setOuterColor(const sf::Color color) {
  m_text->setOutlineColor(color);
}

void
UIText::setCharacterSize(unsigned int newSize) const {
  m_text->setCharacterSize(newSize);
}

void
UIText::setString(const std::string_view newString) {
  m_text->setString(sf::String(newString.data()));
}

void
UIText::draw(sf::RenderTarget* target) const {
  target->draw(*m_text);
}

UIText&
UIText::copy(const UIText& other) {
  this->m_fileStream = other.m_fileStream;
  this->m_font = other.m_font;
  m_text = make_unique<sf::Text>(m_text->getString(), *other.m_font);
  return *this;
}

bool
UIText::internalInit() {
  try {
    m_fileStream = make_shared<sf::FileInputStream>();
    m_font = make_shared<sf::Font>();
    if (nullptr == m_text) {
      m_text = make_unique<sf::Text>();
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return false;
  }

  return true;
}



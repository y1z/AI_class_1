#include "UIText.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "UiRectangle.h"
#include <iostream>

using std::make_shared;
using std::make_unique;

constexpr static std::string_view s_formatsForFonts = "|.ttf|.eot|.otf|.pfb|.pcf|";

UIText::UIText(UIText&& other) noexcept
  : m_text(std::move(other.m_text)),
    m_font(std::move(other.m_font)),
    m_fileStream(std::move(other.m_fileStream))
{
  m_rectPointer = other.m_rectPointer;
  other.m_rectPointer = nullptr;
}

UIText::UIText(const UIText& other)
{
  this->copy(other);
}

UIText&
UIText::operator=(UIText&& other) noexcept {

  if(this != &other)
  {
    m_text = std::move(other.m_text);
    m_font = other.m_font;
    m_fileStream = other.m_fileStream;
    m_rectPointer = other.m_rectPointer;
    other.m_rectPointer = nullptr;
  }


  return *this;
}

UIText&
UIText::operator=(const UIText& other) {
  if(this != &other)
  {
    this->copy(other);
  }
  return *this;
}

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
      m_text->setString(descriptor.textString);
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
UIText::getFillColor() const {
  return m_text->getFillColor();
}

sf::Color
UIText::getOuterColor() const {
  return m_text->getOutlineColor();
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

bool
UIText::makeTextFitSimple(const sf::FloatRect& constraints) {
  auto const bounds = m_text->getLocalBounds();
  const float delta = std::fabsf((bounds.left + bounds.width) - bounds.left);
  {
    const size_t limit = m_text->getString().getSize();

    for (size_t i = 0u; i < limit; ++i) {
      const sf::FloatRect approximetion(m_text->findCharacterPos(i), { .10f, .10f });
      const bool isInsideConstraints = constraints.intersects(approximetion);
      if (!isInsideConstraints) {
        m_textString.insert(i-1, '\n');
      }
    }
  }

  return true;
}

void
UIText::attachToReactangle(UIRectangle* pRect) const {
  m_rectPointer = pRect;
  m_text->setPosition(m_rectPointer->getPosition());
}

void
UIText::unattachFromReactangle() {
  m_rectPointer = nullptr;
}


void
UIText::draw(sf::RenderTarget* target) const {
  target->draw(*m_text);
}

void
UIText::update() {
  const bool isAttached = (nullptr != m_rectPointer);

  if (isAttached) {
    auto bound = m_rectPointer->m_rect.getGlobalBounds();
    m_text->setPosition(bound.left, bound.top);
  }

  m_text->setString(m_textString);
}

UIText&
UIText::copy(const UIText& other) {
  this->m_fileStream = other.m_fileStream;
  this->m_font = other.m_font;
  m_text = make_unique<sf::Text>(m_text->getString(), *m_font);
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



#include "UIText.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "UiRectangle.h"
#include <iostream>
#include <cassert>

using std::make_shared;
using std::make_unique;

constexpr static std::string_view s_formatsForFonts = "|.ttf|.eot|.otf|.pfb|.pcf|";


UIText::UIText(UIText&& other) noexcept

  : m_textString(other.m_textString),
    m_text(std::move(other.m_text)),
    m_font(std::move(other.m_font)),
    m_fileStream(std::move(other.m_fileStream)),
    m_rectPointer(other.m_rectPointer),
    m_alignment(other.m_alignment)

{
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
    m_textString = other.m_textString;
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

  if (nullptr != descriptor.ptrCopyText) {
    this->copy(*descriptor.ptrCopyText);
    return true;
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
      m_textString = descriptor.textString;
      m_text->setString(m_textString);
      m_alignment = descriptor.alignment;
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
UIText::setAlignment(const TEXT_ALIGNMENT::E alignment) {
  m_alignment = alignment;
}


bool
UIText::makeTextFitSimple(const sf::FloatRect& constraints) {
  auto const bounds = m_text->getLocalBounds();
  const float delta = std::fabsf((bounds.left + bounds.width) - bounds.left);
  {
    auto pair = this->isTextInsideHorizontalContraints(constraints);
    bool isIside = pair.first;
    while (!isIside) {
      m_textString.insert(pair.second, "-");
      m_text->setString(m_textString);
      update();

      pair = this->isTextInsideHorizontalContraints(constraints);
      isIside = true;
    }

  }

  return true;
}


void
UIText::attachToReactangle(UIRectangle* pRect) const {
  m_rectPointer = pRect;

  alignText();
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
    alignText();
  }

  m_text->setString(m_textString);
}

UIText&
UIText::copy(const UIText& other) {
  this->m_fileStream = other.m_fileStream;
  this->m_font = other.m_font;
  m_textString = other.m_text->getString();
  m_text = make_unique<sf::Text>(m_textString, *m_font);
  return *this;
}


void
UIText::alignText() const {
  assert(nullptr != m_rectPointer);
  const auto bound = m_rectPointer->m_rect.getGlobalBounds();
  switch (m_alignment) {
  case TEXT_ALIGNMENT::E::centerAlign:
  {
    const float halfHeight = bound.top - (bound.height / 2);
    const float halfWidth = bound.left + (bound.width / 2);
    m_text->setPosition(halfWidth, halfHeight);

  }
  break;

  case TEXT_ALIGNMENT::E::leftAlign:
  [[fallthrough]];
  default:
  m_text->setPosition(bound.left, bound.top);
  break;
  }

}

std::pair<bool, uint64_t>
UIText::isTextInsideHorizontalContraints(const sf::FloatRect& constraints)const {
  const uint64 limit = static_cast<uint64>(m_text->getString().getSize() - 1);
  for (uint64 i = 0u; i < limit; ++i) {
    const sf::FloatRect approximetion(m_text->findCharacterPos(i), { .10f, .10f });
    const bool isInsideConstraints = constraints.intersects(approximetion);

    if (!isInsideConstraints) {
      return std::pair<bool, uint64_t>(false, i);
    }

  }
  return std::pair<bool, uint64_t>(true, static_cast<uint64_t>(-1));
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



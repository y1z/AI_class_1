#pragma once
#include <string_view>


/**
 * Represents a string_view with a associated index
 */
class SpriteSheetAndPortriat
{
public:
  SpriteSheetAndPortriat() = default;
  constexpr SpriteSheetAndPortriat(std::string_view spriteSheet,
                                   std::string_view portriat,
                                   const int64_t index)
  : m_spriteSheet(spriteSheet),
    m_portriat(portriat),
    m_index(index)
  {}


  constexpr bool
  operator<(const SpriteSheetAndPortriat& other)const {
    return m_index < other.m_index;
  }

  constexpr bool
  operator>(const SpriteSheetAndPortriat& other)const {
    return !this->operator<(other);
  }

  constexpr bool
  operator==(const SpriteSheetAndPortriat& other)const {
    return m_index == other.m_index;
  }

  std::string_view m_spriteSheet;
  std::string_view m_portriat;
  int64_t m_index;
};


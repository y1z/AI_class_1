#pragma once
#include <string_view>


/**
 * Represents a string_view with a associated index
 */
class StringViewAndIndex
{
public:
  StringViewAndIndex() = default;
  constexpr StringViewAndIndex(std::string_view view,
                               const int64_t index);


  constexpr bool
  operator<(const StringViewAndIndex& other)const {
    return m_index < other.m_index;
  }

  constexpr bool
  operator>(const StringViewAndIndex& other)const {
    return !this->operator<(other);
  }

  constexpr bool
  operator==(const StringViewAndIndex& other)const {
    return m_index == other.m_index;
  }

  std::string_view m_string;
  int64_t m_index;
};


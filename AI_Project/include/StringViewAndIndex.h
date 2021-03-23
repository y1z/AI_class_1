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
                               const int64_t index,
                               const bool calculateHash);

  constexpr size_t
  hash()
  {
    return std::hash<std::string_view>{}(m_string);
  }

  std::string_view m_string;
  int64_t m_index;
  size_t m_hash = 0;
};


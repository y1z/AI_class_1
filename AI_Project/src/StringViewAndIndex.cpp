#include "StringViewAndIndex.h"

constexpr
StringViewAndIndex::StringViewAndIndex(std::string_view view,
                                       const int64_t index)
  : m_string(view),
    m_index(index)
{}

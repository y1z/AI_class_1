#include "StringViewAndIndex.h"

constexpr
StringViewAndIndex::StringViewAndIndex(std::string_view view,
                                       const int64_t index,
                                       const bool calculateHash)
  : m_string(view),
    m_index(index)
{
  if (calculateHash) {
    m_hash = hash();
  }
}

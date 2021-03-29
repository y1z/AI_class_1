#include "StringSequence.h"
#include <iterator>


StringSequence::StringSequence()
  : m_index(0u)
{}

StringSequence::StringSequence(const std::initializer_list<std::string> initList)
  : StringSequence()
{
  init(initList);
}

void
StringSequence::init(const std::initializer_list<std::string> initList) {
  if (!m_sequence.empty()) {
    m_sequence.clear();
  }
  m_sequence.reserve(initList.size());
  std::move(cbegin(initList), cend(initList), std::back_inserter(m_sequence));
}

const std::string&
StringSequence::getCurrentString() const {
  return m_sequence[m_index];
}

std::string
StringSequence::getCurrentStringCopy() const {
  const std::string result(m_sequence[m_index]);
  return result;
}

const std::string&
StringSequence::getNextString() {
  advanceSequence();
  return getCurrentString();
}

std::string
StringSequence::getNextStringCopy() {
  return std::string(getNextString());
}

uint64_t
StringSequence::getSequenceSize() const {
  return m_sequence.size();
}

uint64_t
StringSequence::advanceSequence() {
  m_index = (m_index + 1u) % m_sequence.size();
  return m_index;
}

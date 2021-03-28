#pragma once
#include <string>
#include <vector>

/**
 * Represents a sequence of string to be used in a certain order.
 */
class StringSequence
{
 public:
  StringSequence();
  StringSequence(const std::initializer_list<std::string>& initList);

  /**
   * Initializes the sequence.
   */
  void
  init(const std::initializer_list<std::string>& initList);

  /**
   * @return
   *  A reference to the current element on the sequence
   */
  const std::string&
  getCurrentString() const;

  /**
   * The same as
   * advanceSequence();
   * return getCurrentString();
   *
   * @see advanceSequence();
   */
  const std::string&
  getNextString();

  /**
   * Advance the currently selected element in the sequence
   * @NOTE : sequence wraps around
   * @return
   *  The index of the current element
   */
  uint64_t
  advanceSequence();

 private:
  /**
   * Contains the Sequence
   */
  std::vector<std::string> m_sequence;

  /**
   * Keeps track of the selected element in the index.
   */
  uint64_t m_index;
};


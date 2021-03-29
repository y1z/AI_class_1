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
  [[nodiscard]] const std::string&
  getCurrentString() const;

  /**
   * @returns
   *  A copy to the current string.
   */
  [[nodiscard]] std::string
  getCurrentStringCopy()const;


  /**
   * The same as
   * advanceSequence();
   * return getCurrentString();
   *
   * @see advanceSequence();
   */
  [[nodiscard]] const std::string&
  getNextString();

  /**
   * @see getNextString
   * The same as getNextString but returns a copy
   *
   * @returns
   *  A copy of the next string
   */
  [[nodiscard]] std::string
  getNextStringCopy();

  /**
   * @returns
   *  The amount of elements in the sequence.
   */
  uint64_t
  getSequenceSize()const;

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


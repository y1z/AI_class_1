#pragma once
#include <cstdint>

/**
* @brief Keeps track of a index
*/
class IndexTracker 
{
public:

  /**
   * @brief increments the index.
   * @returns the index after the increment.
   * @Note It's possible to increment by a negative number.
   */
  int64_t 
  incrementIndex();

  /**
  * @brief resets the current index.
  */
  void
  resetIndex();

  /**
  * @brief The current index.
  */
  [[nodiscard]] int64_t
  getCurrentIndex()const;

  /** @returns a previous index. */
  [[nodiscard]] int64_t
  getPrevIndex() const;

  /**
  * @returns The amount the index is incremented by.
  */
  [[nodiscard]] int64_t 
  getIncrementAmount()const;

  /**
  * @brief sets the amount they increase the index.
  */
  void 
  setIncrementAmount(const int64_t newIncrementAmount);

  /**
  * @brief sets the current index.
  */
  void
  setCurrentIndex(const int64_t newCurrentIndex);


private:
  int64_t m_currentIndex = 0;

  int64_t m_incrementAmount = 1;

public:
  int64_t  m_resetAmount = 0;

};


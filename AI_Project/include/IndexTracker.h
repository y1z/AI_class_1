#pragma once
#include <cstdint>

/**
* @brief Keeps track of a sceneIndex
*/
class IndexTracker 
{
public:

  /**
   * @brief increments the sceneIndex.
   * @returns the sceneIndex after the increment.
   * @Note It's possible to increment by a negative number.
   */
  int64_t 
  incrementIndex();

  /**
  * @brief resets the current sceneIndex.
  */
  void
  resetIndex();

  /**
  * @brief The current sceneIndex.
  */
  [[nodiscard]] int64_t
  getCurrentIndex()const;

  /** @returns a previous sceneIndex. */
  [[nodiscard]] int64_t
  getPrevIndex() const;

  /**
  * @returns The amount the sceneIndex is incremented by.
  */
  [[nodiscard]] int64_t 
  getIncrementAmount()const;

  /**
  * @brief sets the amount they increase the sceneIndex.
  */
  void 
  setIncrementAmount(const int64_t newIncrementAmount);

  /**
  * @brief sets the current sceneIndex.
  */
  void
  setCurrentIndex(const int64_t newCurrentIndex);


private:
  int64_t m_currentIndex = 0;

  int64_t m_incrementAmount = 1;

public:
  int64_t  m_resetAmount = 0;

};


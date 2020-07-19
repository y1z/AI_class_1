#pragma once
#include <cstdint>
#include <cstddef>

/**
* @brief Keeps track 
*/
class IndexTracker 
{
public:

  void
  incrementIndex();

  /**
  * @brief resets the current index.
  */
  void
  resetIndex();

  /**
  * @brief The current index.
  */
  size_t
  getCurrentIndex()const;

  /**
  * @returns The amount the index is incremented by.
  */
  int32_t 
  getIncrementAmount()const;

  /**
  * @brief sets the amount they increase the index.
  */
  void 
  setIncrementAmount(const int32_t newIncrementAmount);

  /**
  * @brief sets the current index.
  */
  void
  setCurrentIndex(const size_t newCurrentIndex);


private:
  size_t m_currentIndex = 0;

public:
  size_t m_resetAmount = 0;

private:
  int32_t m_incrementAmount = 1;
};


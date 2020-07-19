#include "IndexTracker.h"

void 
IndexTracker::incrementIndex()
{
  m_currentIndex += m_incrementAmount;
}

void
IndexTracker::resetIndex()
{
  m_currentIndex = m_resetAmount;
}

size_t
IndexTracker::getCurrentIndex() const
{
  return m_currentIndex;
}

int32_t 
IndexTracker::getIncrementAmount() const
{
  return m_incrementAmount;
}

void
IndexTracker::setIncrementAmount(int32_t const newIncrementAmount)
{
  m_incrementAmount = newIncrementAmount; 
}

void 
IndexTracker::setCurrentIndex(const size_t newCurrentIndex)
{
  m_currentIndex = newCurrentIndex;
}

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

int64_t 
IndexTracker::getCurrentIndex() const
{
  return m_currentIndex;
}

int64_t 
IndexTracker::getIncrementAmount() const
{
  return m_incrementAmount;
}

void
IndexTracker::setIncrementAmount( const int64_t newIncrementAmount)
{
  m_incrementAmount = newIncrementAmount; 
}

void 
IndexTracker::setCurrentIndex(const int64_t newCurrentIndex)
{
  m_currentIndex = newCurrentIndex;
}

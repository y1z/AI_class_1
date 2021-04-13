#include "RotationSegment.h"
#include "util.h"
#include "GlobalValues.h"



float
RotationSegment::getRotationDelta() const {
  return m_end.getAngle() - m_start.getAngle();
}

float
RotationSegment::getDifferenceFrom(const float radians) const {
  const auto differenceFromStart = std::fabsf(radians - m_start.getAngle());
  const auto differenceFromEnd = std::fabsf(radians - m_end.getAngle());
  return std::min(differenceFromStart, differenceFromEnd);
}

float
RotationSegment::getDifferenceFrom(const Vec2& direction) const {
  return getDifferenceFrom(direction.normalize().getAngle());
}

std::pair<float, float>
RotationSegment::getAnglesFromStartAndEnd() const {
  return std::pair<float, float>(m_start.getAngle(), m_end.getAngle());
}

bool
RotationSegment::isInRange(const Vec2 direction) const {
  const auto angle = direction.getAngle();
  const auto startAngle = m_start.getAngle();
  const auto endAngle = m_end.getAngle();
  return util::isInRange(std::min(endAngle, startAngle),
                         std::max(endAngle, startAngle),
                         angle);
}

RotationSegment&
RotationSegment::rotateRadians(const float radians) {
  m_start.rotateSelfBy(radians);
  m_end.rotateSelfBy(radians);
  return *this;
}

RotationSegment&
RotationSegment::rotateToOppositeQuadrant() {
  return rotateRadians(gvar::pi);
}

RotationSegment&
RotationSegment::rotateEnd(const float radians) {
  m_end.rotateSelfBy(radians);
  return *this;
}

RotationSegment&
RotationSegment::rotateEndToOppositeQuadrant() {
  return rotateEnd(gvar::pi);
}



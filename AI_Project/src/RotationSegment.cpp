#include "RotationSegment.h"
#include "util.h"


Vec2
RotationSegment::getRotationDelta() const {
  return end - start;
}

float
RotationSegment::getDifferenceFrom(const float radians) const {
  return std::min(radians - start.getAngle(), radians - end.getAngle());
}

bool
RotationSegment::isInRange(const Vec2 direction) const {
  const auto angle = direction.getAngle();
  const auto startAngle = start.getAngle();
  const auto endAngle = end.getAngle();
  return util::isInRange(std::min(endAngle, startAngle),
                         std::max(endAngle, startAngle),
                         angle);
}

RotationSegment&
RotationSegment::rotateRadians(const float radians) {
  start.rotateSelfBy(radians);
  end.rotateSelfBy(radians);
  return *this;
}

//RotationSegment
//RotationSegment::operator+(const RotationSegment& otherSegment)const {
//  const float otherSegmentDelta = otherSegment.getRotationDelta();
//  return RotationSegment(otherSegment.start.a + otherSegmentDelta,
//                         otherSegment.end + otherSegmentDelta);
//}
//
//RotationSegment
//RotationSegment::operator-(const RotationSegment& otherSegment) const {
//  const float otherSegmentDelta = otherSegment.getRotationDelta();
//  return RotationSegment(otherSegment.start - otherSegmentDelta,
//                         otherSegment.end - otherSegmentDelta);
//}

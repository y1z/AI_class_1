#include "RotationSegment.h"
#include <cmath>
#include "util.h"


float
RotationSegment::getRotationDelta() const {
  return end - start;
}

float
RotationSegment::getDifferenceFrom(const float radians) const {
  return std::min(std::fabsf(radians - start), std::fabsf(radians - end));
}

bool
RotationSegment::isInRange(const float radians) const {
  return util::isInRange(std::min(end, start), std::max(end, start), radians);
}

RotationSegment&
RotationSegment::rotateRadians(const float radians) {
  start += radians;
  end += radians;
  return *this;
}

RotationSegment
RotationSegment::operator+(const RotationSegment& otherSegment)const {
  const float otherSegmentDelta = otherSegment.getRotationDelta();
  return RotationSegment(otherSegment.start + otherSegmentDelta,
                         otherSegment.end + otherSegmentDelta);
}

RotationSegment
RotationSegment::operator-(const RotationSegment& otherSegment) const {
  const float otherSegmentDelta = otherSegment.getRotationDelta();
  return RotationSegment(otherSegment.start - otherSegmentDelta,
                         otherSegment.end - otherSegmentDelta);
}

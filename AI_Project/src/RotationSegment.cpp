#include "RotationSegment.h"
#include <cmath>

float
RotationSegment::getRotationDelta() const {
  return start - end;
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

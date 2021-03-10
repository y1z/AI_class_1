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

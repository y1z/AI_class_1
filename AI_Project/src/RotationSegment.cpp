#include "RotationSegment.h"
#include "util.h"


float
RotationSegment::getRotationDelta() const {
  return end.getAngle() - start.getAngle();
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


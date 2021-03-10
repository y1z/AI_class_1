#pragma once



/**
 * Describe a partial rotation of a circle in radians
 */
struct RotationSegment {
  RotationSegment(const float _start, const float _end)
    :start(_start), end(_end) {}

  float
  getRotationDelta()const;

  /**
   * @returns
   *  The rotation after being altered.
   */
  RotationSegment&
  rotateRadians(const float radians);


  /**
   * Adds 2 rotation segment together
   */
  RotationSegment
  operator+ (const RotationSegment& otherSegment);

  RotationSegment
  operator- (const RotationSegment& otherSegment);


  float start;
  float end;
};


#pragma once



/**
 * Describe a partial rotation of a circle in radians
 */
struct RotationSegment {
  RotationSegment(const float _start, const float _end)
    :start(_start), end(_end) {}

  /**
   * @returns
   *  The delta between the variables 'start' and 'end'.
   */
  float
  getRotationDelta()const;

  /**
   * @returns
   *  true when the parameter passed in, is within the range of the RotationSegment.
   */
  bool
  isInRange(const float radians)const;

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
  operator+ (const RotationSegment& otherSegment)const ;

  /**
   * Subtracts 2 rotation from each-other
   */
  RotationSegment
  operator- (const RotationSegment& otherSegment)const;


  float start;
  float end;
};


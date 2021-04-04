#pragma once
#include "Vec2.h"



/**
 * Describe a partial rotation of a circle in radians
 */
struct RotationSegment
{
  RotationSegment(const float _start, const float _end)
    :start(Vec2(1.0f, 0.0f).rotate(_start)),
    end(Vec2(1.0f, 0.0f).rotate(_end)) {}

  RotationSegment(const Vec2 _start, const Vec2 _end)
    :start(_start.normalize()),
    end(_end.normalize()) {}

  /**
   * @returns
   *  The delta between the variables 'start' and 'end'.
   */
  float
  getRotationDelta()const;


  /**
   * @returns
   *  The delta between the variables 'start' and 'end'.
   */
  float
  getDifferenceFrom(const float radians)const;

  /**
   * @returns
   *  true when the parameter passed in, is within the range of the RotationSegment.
   */
  bool
  isInRange(const Vec2 direction)const;

  /**
   * @returns
   *  The rotation after being altered.
   */
  RotationSegment&
  rotateRadians(const float radians);


  Vec2 start;
  Vec2 end;
};


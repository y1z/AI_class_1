#pragma once
#include "Vec2.h"



/**
 * Describe a partial rotation of a circle in radians
 */
struct RotationSegment
{
  RotationSegment(const float _start, const float _end)
    :m_start(Vec2(1.0f, 0.0f).rotate(_start)),
    m_end(Vec2(1.0f, 0.0f).rotate(_end)) {}

  RotationSegment(const Vec2 _start, const Vec2 _end)
    :m_start(_start.normalize()),
    m_end(_end.normalize()) {}

  /**
   * @returns
   *  The delta between the variables 'm_start' and 'm_end'.
   */
  float
  getRotationDelta()const;

  /**
   * @returns
   *  The delta between the input and the closest of the
   *  2 variables 'm_start' 'm_end'.
   */
  float
  getDifferenceFrom(const float radians)const;

  /**
   * @see getDifferenceFrom
   */
  float
  getDifferenceFrom(const Vec2& direction)const;

  /**
   * @see getDifferenceFrom
   */
  float
  getDifferenceFrom(const RotationSegment& rotation)const;

  /**
   * @returns
   *  The pair that contains the angle from 'm_start'(.first) and 'm_end'(.second)
   */
  std::pair<float, float>
  getAnglesFromStartAndEnd()const;

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

  /**
   * @returns
   *  The rotation after being altered.
   */
  RotationSegment&
  rotateToOppositeQuadrant();

  /**
   * Rotates the 'm_end' variable by a x amount of radians
   */
  RotationSegment&
  rotateEnd(const float radians);

  /**
   * Rotate the 'm_end' variable to the opposite quadrant aka 180 degrees or pi radians
   */
  RotationSegment&
  rotateEndToOppositeQuadrant();

  /**
   * Where the rotation starts
   */
  Vec2 m_start;

  /**
   * Where the rotation ends.
   */
  Vec2 m_end;
};


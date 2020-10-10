#pragma once
#include "Vec2.h"

/**
 * @class Edge2D : represents a 2d edge
 */
class Edge2D 
{
public:
  Edge2D(const Vec2& Start,const Vec2& End);
private:

  enum class Orientation 
  {
    clockwise,
    counterClockwise,
    collinear,
  };

public:

  [[nodiscard]] Edge2D
  move(const Vec2& offSet) const;

  Edge2D&
  moveSelf(const Vec2& offSet);

  /** @brief check if 2 edges are intersecting*/
  bool
  isIntersecting(const Edge2D &otherEdges) const;
private:

  Orientation
  calculateRotation(const Vec2& edge1Point1,
                    const Vec2& edge1Point2,
                    const Vec2& edge2PointAny/* <- any of the 2 points from the other edge*/)const;

public:
  /** @brief the start of the edge.*/
  Vec2 m_startOfEdge;
  /** @brief the end of the edge.*/
  Vec2 m_endOfEdge;
};


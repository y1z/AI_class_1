#pragma once
#include "Vec2.h"

/**
 * @class Edge2D : represents a 2d edge
 */
class Edge2D 
{
public:

  Edge2D();
  Edge2D(const Vec2& Start,const Vec2& End);

  Edge2D(const Edge2D&) = default;
  Edge2D(Edge2D&&) noexcept = default;
public:
  Edge2D& operator =(const Edge2D&) = default;
  Edge2D& operator =(Edge2D&&) noexcept = default;
public:

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

  /**
   * @returns a normal of the edge 
   * @param orientation : which side of the edge should the normal com from.
   */
  Edge2D
  getNormal(const Edge2D::Orientation orientation)const;


private:
  /**
   * @brief used internally to know if a edge is intersecting with different edges
   */
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


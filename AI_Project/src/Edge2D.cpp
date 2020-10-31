#include "Edge2D.h"
#include "util.h"
#include "GlobalValues.h"

Edge2D::Edge2D()
  : Edge2D(Vec2(0, 0), Vec2(0, 1))
{}

Edge2D::Edge2D(const Vec2& Start, const Vec2& End)
  : m_startOfEdge(Start), m_endOfEdge(End)
{}

Edge2D 
Edge2D::move(const Vec2 & offSet) const
{
  return Edge2D(m_startOfEdge + offSet,
                m_endOfEdge + offSet);
}

Edge2D&
Edge2D::moveSelf(const Vec2& offSet)
{
  this->m_startOfEdge += offSet;
  this->m_endOfEdge += offSet;
  return *this;
}

bool 
Edge2D::isIntersecting(const Edge2D& otherEdges) const
{
  const Edge2D::Orientation dir1 = calculateRotation(this->m_startOfEdge, this->m_endOfEdge, otherEdges.m_startOfEdge);
  const Edge2D::Orientation dir2 = calculateRotation(this->m_startOfEdge, this->m_endOfEdge, otherEdges.m_endOfEdge);
  const Edge2D::Orientation dir3 = calculateRotation(otherEdges.m_startOfEdge, otherEdges.m_endOfEdge, this->m_startOfEdge);
  const Edge2D::Orientation dir4 = calculateRotation(otherEdges.m_startOfEdge, otherEdges.m_endOfEdge, this->m_endOfEdge);

  return ( dir1 != dir2 && dir3 != dir4 );
}

Edge2D 
Edge2D::getNormal(Edge2D::Orientation orientation) const
{
  assert(orientation != Edge2D::Orientation::collinear && " invalid orientation ");

  const float rotationAngle = 
    (Edge2D::Orientation::counterClockwise == orientation) ? gvar::halfPi : -gvar::halfPi;

  const Vec2 edgeCenter = (m_endOfEdge - m_startOfEdge) * 0.5f;
  const Vec2 normalDir = (edgeCenter * 2.0f).normalize().rotate(rotationAngle);

  return Edge2D(edgeCenter, edgeCenter + normalDir);
}

Edge2D::Orientation 
Edge2D::calculateRotation(const Vec2& edge1Point1,
                          const Vec2& edge1Point2,
                          const Vec2& edge2PointAny) const
{
  const int val =
   (edge1Point2.y - edge1Point1.y) *
   (edge2PointAny.x - edge1Point2.x) -

   (edge1Point1.x - edge1Point2.x) *
   (edge2PointAny.y - edge1Point2.y);

  if(val == 0 )
  {
    return Orientation::collinear;
  }
  else if(val < 0 )
  {
    return Orientation::counterClockwise;
  }

  return Orientation::clockwise;
}

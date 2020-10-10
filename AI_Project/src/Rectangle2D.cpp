#include "Rectangle2D.h"

Rectangle2D::Rectangle2D(
  const Vec2& topLeft,
  const Vec2& topRight,
  const Vec2& bottomRight,
  const Vec2& bottomLeft)
  
  :m_topLeft(topLeft),
  m_topRight(topRight),
  m_bottomRight(bottomRight),
  m_bottomLeft(bottomLeft)
{}

void
Rectangle2D::encapsulateCircle(const Vec2& circleCenterPoint,
                               const float circleRadius)
{
  const Vec2 rightOffSet = Vec2::rightVector2 * circleRadius;
  const Vec2 leftOffSet = Vec2::leftVector2 * circleRadius;
  const Vec2 downOffSet = Vec2::downVector2 * circleRadius;
  const Vec2 upOffSet = Vec2::upVector2 * circleRadius;

  m_bottomLeft = circleCenterPoint + (leftOffSet + downOffSet);
  m_bottomRight = circleCenterPoint + (rightOffSet + downOffSet);
  m_topRight = circleCenterPoint + (rightOffSet + upOffSet);
  m_topLeft = circleCenterPoint + (leftOffSet + upOffSet);

}

Rectangle2D&
Rectangle2D::moveSelf(const Vec2& offSet)
{
  m_bottomRight += offSet;
  m_bottomLeft += offSet;
  m_topRight += offSet;
  m_topLeft += offSet;

  return *this;
}

Rectangle2D 
Rectangle2D::move(const Vec2& offSet) const
{
  return Rectangle2D(m_topLeft + offSet,
                     m_topRight + offSet,
                     m_bottomRight + offSet,
                     m_bottomLeft + offSet);
}

Edge2D 
Rectangle2D::returnEdge(uint8_t whichEdge) const
{
  return Edge2D(m_array[whichEdge],m_array[whichEdge + 1]);
}


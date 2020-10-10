#pragma once
#include "Vec2.h"
#include "Edge2D.h"

/**
 * @class Rectangle2D : Represents a 2d rectangle
 */
class Rectangle2D 
{
public:
  Rectangle2D(const Vec2& topLeft,
              const Vec2& topRight,
              const Vec2& bottomRight,
              const Vec2& bottomLeft);
public:

  
  union 
  {

    struct 
    {
      /** The top left point of a rectangle*/
      Vec2 m_topLeft;

      /** The top right point of a rectangle*/
      Vec2 m_topRight;

      /** The bottom right point of a rectangle*/
      Vec2 m_bottomRight;

      /** The bottom left point of a rectangle*/
      Vec2 m_bottomLeft;

    };

    Vec2 m_array[4];
  };


  float m_angle = 0.00f;

public:

/**
 * @brief moves the points of a rectangle to surround a circle.
 * @param circleCenterPoint : where the center of the circle is located.
 * @param circleRadius : the radius of the circle
 */
  void
  encapsulateCircle(const Vec2& circleCenterPoint,
                    const float circleRadius);

/**
 * @brief moves the rectangle.
 */
  Rectangle2D&
  moveSelf(const Vec2& offSet);

/**
 * @brief moves the rectangle.
 * @returns a different rectangle
 */
  [[nodiscard]] Rectangle2D
  move(const Vec2& offSet) const;

/**
 * @returns a edge of the rectangle.
*/ 
  Edge2D
  returnEdge(uint8_t whichEdge) const;

};


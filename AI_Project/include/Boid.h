#pragma once
#include "vec2.h"

class Boid
{
public:

  /**
  * @returns A vector that goes to the destination
  * @bug no known bugs.
  * @param[in] strength controls the length of the vector.
  */
  vec2 
  seek(vec2 const& currentPos,
       vec2 const& destination,
       float const strength = 1.0f) const;

  /**
  * @returns A vector that goes to the destination
  * @bug no known bugs.
  * @param[in] strength controls the length of the vector.
  */
  vec2
  flee(vec2 const& currentPos,
       vec2 const& destination,
       float const strength = 1.0f,
       float const radius = 100.0f)const;//

  vec2
  arrive(vec2 const& currentPos,
         vec2 const& destination,
         float const strength = 1.0f,
         float const radius = 100.0f)const;


public:

vec2 m_position;


};


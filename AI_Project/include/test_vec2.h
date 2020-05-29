#pragma once
#include "vec2.h"
  /**
  * @brief This file only purpose is for testing the "vec2" class
  */

inline bool testDotProduct()
{
  vec2 up (0.0f,1.0f);
  vec2 down(0.0f,-1.0f);
  vec2 left(1.0f, 0.0f);
  vec2 right(-1.0f, 0.0f);

  if( -1.0f != up.dot(down) &&
     -1.0f != down.dot(up) &&
     -1.0f != left.dot(right) &&
     -1.0f != right.dot(left) )
  {
    return false;
  }

  if( 1.0f != up.dot(up) &&
     1.0f != down.dot(down) &&
     1.0f != left.dot(left) &&
     1.0f != right.dot(right))
  {
    return false;
  }

  return true;
}

inline bool testNormalize()
{
  vec2 up(0.0f,100.0f);
  bool isSucceful = true;

  if( vec2(0.0f, 1.0f) != up.normalize() )
  {
    isSucceful = false;
  }

  vec2 downRight(50.0f,-50.0f);

  if( vec2(0.707f, -0.707f) != downRight.normalize() )
  {
    isSucceful = false;
  }

  vec2 downLeft(-50.0f,-50.0f);

  if( vec2(-0.707f, -0.707f) != downLeft.normalize() )
  {
    isSucceful = false;
  }
  return isSucceful;
}

inline bool testEverthing()
{
  bool isSuccesful = testDotProduct();
  if(!isSuccesful )
  { std::cout << "dot product failed \n ";}
  
  isSuccesful = testNormalize();

  if(!isSuccesful )
  { std::cout << "normalizing failed \n";}

  return isSuccesful;
}

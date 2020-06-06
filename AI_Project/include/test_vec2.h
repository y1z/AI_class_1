#pragma once
#include "Vec2.h"
#include <iostream>
/**
* @brief This file only purpose is for testing the "Vec2" class
*/

inline bool testDotProduct()
{
  Vec2 up (0.0f,1.0f);
  Vec2 down(0.0f,-1.0f);
  Vec2 left(1.0f, 0.0f);
  Vec2 right(-1.0f, 0.0f);

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
  Vec2 up(0.0f,100.0f);
  bool isSucceful = true;

  if( Vec2(0.0f, 1.0f) != up.normalize() )
  {
    isSucceful = false;
  }

  Vec2 downRight(50.0f,-50.0f);

  if( Vec2(0.707f, -0.707f) != downRight.normalize() )
  {
    isSucceful = false;
  }

  Vec2 downLeft(-50.0f,-50.0f);

  if( Vec2(-0.707f, -0.707f) != downLeft.normalize() )
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

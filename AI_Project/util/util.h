#pragma once
#include <random>
#include <cassert>
#include "Types.h"

namespace util 
{

  static float
  randomRangeFloat(const float minimum, const float maximum)
  {
    assert(maximum > minimum);
    constexpr static float inverseMaximum = 1.0f / RAND_MAX;
    const float delta = maximum - minimum;

    return  minimum + (inverseMaximum * std::rand() * delta);
  }
  
}

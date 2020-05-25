#include <iostream>
#include "vec2.h"
#include "../src/test_vec2.cpp"


int main()
{

  if( false == testEverthing() )
  {
    std::cout << "\n\n=========================\n something failed in the test's\n";
  }
  else
  {
    std::cout << "everything when well \n";
  }


  return 0;
}

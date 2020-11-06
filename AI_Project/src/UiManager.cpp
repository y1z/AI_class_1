#include "UiManager.h"

#include <iostream>


bool 
UiManager::init(const std::vector< UIRectangleDesc >& descriptors)
{
  m_rectangles.reserve(descriptors.size());
  try
  {
    for( const auto& des : descriptors )
    {
      m_rectangles.emplace_back(UiRectangle(des));
    }

  }
  catch( const std::exception& e )
  {
    std::cerr << e.what() << "\n\n";
  }


  return true;
}


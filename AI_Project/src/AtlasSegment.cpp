#include "AtlasSegment.h"
#include <SFML/System/FileInputStream.hpp>
#include <fstream>

bool 
AtlasSegment::init(const std::string_view filePath)
{
  const std::fstream file(filePath.data(), std::ios::in);

  if(file.is_open() )
  {
    
  }

  return false;
}

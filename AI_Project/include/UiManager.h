#pragma once
#include <vector>

#include "UiRectangle.h"

/**
 * @class UiManager : controls the UI.
 */
class UiManager 
{
public:
  using RectangleContainer = std::vector< UiRectangle >;
public:
  
  /**
   * @brief starts the UI Manager.
   */
  bool
  init(const std::vector< UIRectangleDesc >& descriptors);


  /**
   * @
   */
  void
  addRectangle(const UIRectangleDesc& desc);



private:
  RectangleContainer m_rectangles;
};




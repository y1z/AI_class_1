#pragma once
#include "Boid.h"


/**
 * @file
 * @class Racer :
 */
class Racer 
{
public:
  Racer(const BoidDescriptor& desc );

  BoidDescriptor&
  getBoidData();

  const BoidDescriptor&
  getBoidData()const;


  void
  update(float deltaTime);


private:
  Boid m_boid;
};


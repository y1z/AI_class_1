#pragma once
#include "Boid.h"


/**
 * @file
 * @class Racer : contains the racer. 
 */
class Racer 
{
public:
  Racer(const BoidDescriptor& desc );

  /** @returns a reference to the descriptor */
  BoidDescriptor&
  getBoidData();

  /** @returns a reference to the descriptor */
  const BoidDescriptor&
  getBoidData()const;


  /** @returns a reference to the boid itself*/
  Boid&
  getBoid();

  /** @returns a reference to the boid itself*/
  const Boid&
  getBoid() const;

  /** @returns the total amount of laps. */
  uint32 
  getLapCount()const;

  /** @returns the total amount of checkpoints passed.*/
  uint32 
  getCheckpointTotal()const;

  /** @returns the total amount of checkpoints passed of the current lap.*/
  uint32
  getCurrentLapCheckPoint()const;


  void
  update(float deltaTime);

private:
  Boid m_boid;
public:
  LapCount m_lapCount;
};


#pragma once
#include "Boid.h"


/**
 * @file
 * @class Racer : contains the racer. 
 */
class Racer 
{
public:
  Racer(const BoidDescriptor& desc);

  Racer(const Boid& boid);

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

  uint32
  getTotalLap()const;

  /** @returns the total amount of laps. */
  LapCount
  getLapRequirements()const;

  /** @returns the total amount of checkpoints passed.*/
  uint32 
  getCheckpointTotal()const;

  /** @returns the total amount of checkpoints passed of the current lap.*/
  uint32
  getCurrentLapCheckPoint()const;


  void
  update(float deltaTime);

  void
  draw(sf::RenderTarget& target);

  void
  destroy();
private:

  void
  updateLapCount();

private:
  Boid m_boid;
public:
  LapCount m_lapCount;
};


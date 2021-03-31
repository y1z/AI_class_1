#pragma once
#include "Boid.h"
#include "SpriteAtlas.h"

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

  /** @retruns The current frame. */
  size_t
  getCurrentFrame()const;

  /**
   * Lets the frame be manually selected.
   */
  void
  setFrame(const int32 selectedFrame);

  /**
   * Advances the frame in the sprite atlas.
   */
  void
  advanceFrames(const int32 framesToAdvance = 1);

  /**
   * updates the logic for the racer.
   */
  void
  update(float deltaTime);

  /**
   * draws the racers
   * @Note If the racer does NOT have a sprite, the racer will look like a sphere.
   */
  void
  draw(sf::RenderTarget& target);


  void
  destroy();
private:

  void
  updateLapCount();

private:
  size_t m_currentFrame;
public:
  SpriteAtlas* m_atlasPtr = nullptr;
  Boid m_boid;
  LapCount m_lapCount;
};


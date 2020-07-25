#pragma once
#include "soModule.h"
#include "Boid.h"
#include "Types.h"
#include <vector>
#include <deque>

/**
* @brief keeps track of manages global data related with the game must be initialized(start up)
* and ended (shut down) manually.
*/
class GameManager final : public soModule<GameManager>
{
public: // constructors 
  GameManager(const GameManager&) = delete;
  GameManager(GameManager&&) = delete;

  ~GameManager() = default;
public: // operators

  GameManager& 
  operator=(const GameManager&) = delete;

  GameManager&
  operator=(GameManager&&) = delete;

public:// functions

  /**
  * @brief For uninitializing the game-manager.
  */
	void 
  OnShutDown() override;

  /**
  * @brief For initializing the game-manger.
  */
	int
  OnStartUp(void* _Desc) override;

  /**
  * @brief Adds a boid to the game.
  */
  size_t 
  addBoidToGame(BoidDescriptor& descriptor);

  /**
  * @brief For initializing the game-manger.
  * @returns the index for that boid.
  */
  size_t 
  addBoidToGame(Boid& newBoid);

  /**
  * @brief removes a boid from the game.
  * @returns If the Boid was removed.
  */
  bool
  removeBoidFromGame(const size_t index);

  /**
  * @returns The total amount of boids in the game.
  */
  size_t
  getTotalBoids()const;

  /**
  * @returns A references to a Boid.
  */
  Boid&
  getBoidRef(const size_t index);

  /**
  * @returns A pointer to a Boid.
  */
  Boid*
  getBoidPtr(const size_t index);

  std::deque<Boid>::iterator
  getBeginningIter();

  std::deque<Boid>::iterator
  getEndingIter();

private:

  /**
  * @brief Contains every boid in the game.
  * @note It's a deque because I want to have to ability to
  * get pointers and references to the individual Boids.
  */
  std::deque<Boid> m_boids;

public:
  /**
  * @brief Contains every boid in the game.
  */
  std::vector<FollowPathNode> m_globalPath;
};


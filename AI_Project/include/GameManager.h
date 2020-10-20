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
public:
  using containerType = std::deque<Boid>;
public: // constructors 

  GameManager() = default;

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
  * @brief For de-initializing the game-manager.
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
  addBoidToGame(const BoidDescriptor& descriptor);

  /**
  * @brief For initializing the game-manger.
  * @returns the index for that boid.
  */
  size_t 
  addBoidToGame(const Boid& newBoid);
  
  /**
   * @brief add a node to the global path.
   * 
   */
  void 
  addNodeToGlobalPath(const FollowPathNode& node);

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

  /** @returns a iterator to the underlying container. */
  containerType::iterator
  begin();

  /** @returns a iterator to the underlying container. */
  containerType::iterator
  end();

  /** @returns a const iterator to the underlying container. */
  containerType::const_iterator
  cbegin() const;

  /** @returns a const iterator to the underlying container. */
  containerType::const_iterator
  cend() const;

  void
  drawPath(sf::RenderWindow& window) ;

private:

  /**
  * @brief Contains every boid in the game.
  * @note It's a deque because I want to have to ability to
  * get pointers and references to the individual Boids.
  */
  std::deque<Boid> m_groupBoids;

public:
  /**
  * @brief contains the path that every boid can use.
  */
  std::vector<FollowPathNode> m_globalPath;

  /** @brief This is used to draw the path.*/
  sf::VertexArray m_vertexArray;

};


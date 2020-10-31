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
  using containerType = BoidContainer;
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

  void
  setupGroup();

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
   * @param node : the node to be added.
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

  /**
   * @returns A reference to the container.
   */
  const containerType&
  getBoidContainerRef()const;

  /**
   * @returns A reference to the container.
   */
  containerType&
  getBoidContainerRef();

  /**
   * @returns A reference to the container.
   */
  const FollowPath::PathContainer&
  getPathContainerRef()const;

  /**
   * @returns A reference to the container.
   */
  FollowPath::PathContainer
  getPathContainerRef();

  /** @brief draws the path on to a window. */
  void
  drawPath(sf::RenderWindow& window) const ;

  void
  addDebugVertexLine(const Vec2 & start,
                     const Vec2 & end);

  /**
   * @brief 
   */
  void
  addDebugVertexLine(const sf::Vertex& startOfLine,
                     const sf::Vertex& endOfLine);

  void
  drawAndClearDebug(sf::RenderWindow& window);

private:

  /**
  * @brief Contains every boid in the game.
  * @note It's a deque because I want to have to ability to
  * get pointers and references to the individual Boids.
  */
  containerType  m_groupBoids;

public:

  /** 
   * @brief contains the path current used by the game.
   */
  FollowPath m_path;

public:
  sf::VertexArray m_debugLines;
};



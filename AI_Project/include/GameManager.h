#pragma once
#include "soModule.h"
#include "Racer.h"
#include "Types.h"

#include <vector>
#include <deque>

class SpriteAtlas;

/**
* @brief keeps track of manages global data related with the game must be initialized(start up)
* and ended (shut down) manually.
*/
class GameManager final : public soModule<GameManager>
{
public:
  using containerType = RacerContainer;
  using AgentType = Racer;
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
  * @brief adds a racer to the game.
  */
  size_t
  addRacerToGame(const BoidDescriptor& descriptor);

  /**
  * @brief adds a racer to the game.
  */
  size_t
  addRacerToGame(const BoidDescriptor& descriptor,
                 SpriteAtlas* atlas);

  /**
  * @brief For initializing the game-manger.
  * @returns the index for that boid.
  */
  size_t
  addRacerToGame(const Boid& newBoid);


  size_t
  addRacerToGame(const Racer& racer);

  /**
   * @brief add a node to the global path.
   * @param node : the node to be added.
   *
   */
  void
  addNodeToGlobalPath(const FollowPathNode& node);


  void
  setLapTotal(const uint32 requiredLapCount);

  /**
  * @brief removes a boid from the game.
  * @returns If the Boid was removed.
  */
  bool
  removeBoidFromGame(const size_t index);


  /**
   * @return the current lap requirement for the race.
   */
  LapCount
  getLapRequirements()const;

  /**
  * @returns The total amount of boids in the game.
  */
  size_t
  getTotalBoids()const;

  /**
  * @returns A references to the Agent.
  */
  AgentType&
  getAgentRef(const size_t index);

  /**
  * @returns A pointer to the Agent.
  */
  AgentType*
  getAgentPtr(const size_t index);

  /**
   * @returns A reference to the container.
   */
  const containerType&
  getAgentContainerRef()const;

  /**
   * @returns A reference to the container.
   */
  containerType&
  getAgentContainerRef();

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
  drawRacers(sf::RenderWindow& window);

  /**
   * @brief used to create lines that only appear during debugging.
   */
  void
  addDebugVertexLine(const Vec2 & start,
                     const Vec2 & end);

  /**
   * @brief used to create lines that only appear during debugging.
   */
  void
  addDebugVertexLine(const sf::Vertex& startOfLine,
                     const sf::Vertex& endOfLine);

  /**
   * @brief draws the lines used for debugging then remove them from the container.
   */
  void
  drawAndClearDebug(sf::RenderWindow& window);


private:

  /**
  * @brief Contains every boid in the game.
  * @note It's a deque because I want to have to ability to
  * get pointers and references to the individual Boids.
  */
  containerType  m_groupAgents;

public:

  /**
   * @brief contains the path current used by the game.
   */
  FollowPath m_path;

private:
  /**
   * @brief controls how many laps are required to finish a race.
   */
  LapCount m_lapRequirements;
public:
  sf::VertexArray m_debugLines;
};



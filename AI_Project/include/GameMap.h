#pragma once
#include <filesystem> // for std::filesystem::path
#include <memory>
#include "Types.h"

/**
 * Represents the map (paths, visuals)
 */
class GameMap
{
public:
  using mapPathContainer = std::vector<FollowPathNode>;
  using visualsContainer = std::vector<std::unique_ptr<sf::Shape>>;
public:
  GameMap();

  /**
   * @brief loads the map from a file.
   */
  bool
  loadMap(const std::filesystem::path& pathToMap);

  /**
   * @brief saves the current map to a file.
   */
  bool
  saveMap(const std::string_view saveFilePath);

  /**
   * Draws the map
   */
  void
  draw(sf::RenderWindow& window);


  /**
   * used to create a map.
   * @param[in] mapData
   * Contains all the position necessary for creating the map.
   */
  void
  createMap(const std::vector<FollowPathNode>& mapData);

  /**
   * @copydocs GameMap::createMap()
   */
  void
  createMap(std::vector<FollowPathNode>&& mapData);

  /**
   * Adds a node to the game map.
   */
  void
  addNode(const FollowPathNode& newNode);


  /**
   * clear out the track
   */
  void
  clear();

  /**
   * @returns
   *  The requirements for finishing the race.
   */
  LapCount
  getLapRequiements()const;


  /**
   * @returns A begin iterator.
   *
   * This function exist just to be used in ranged for loops.
   */
  mapPathContainer::iterator
  begin();

  /**
   * @returns A begin iterator.
   *
   * This function exist just to be used in ranged for loops.
   */
  mapPathContainer::const_iterator
  cbegin()const;


  /**
   * @returns A end iterator.
   *
   * This function exist just to be used in ranged for loops.
   */
  mapPathContainer::iterator
  end();

  /**
   * @returns A end iterator.
   *
   * This function exist just to be used in ranged for loops.
   */
  mapPathContainer::const_iterator
  cend()const;

private:
  /**
   * @returns A float extracted from the data
   */
  float
  extractRadiusFrom(const std::string& data,
                    const size_t currentIndex)const;

  /**
   * @returns A Vec2 extracted from the data.
   */
  Vec2
  extractPositionFrom(const std::string& data,
                      const size_t currentIndex)const;

public:

  /**
   * Contains the data for the shape of the map.
   */
  mapPathContainer m_positionData;
private:

  /**
   * Contains the data for drawing the Map
   */
  visualsContainer m_visuals;

  /**
   * Keeps track of the requirements for finishing a track.
   */
  LapCount m_requirements;
};


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
   */
  void
  createMap(const std::vector<FollowPathNode>& mapData);



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

  mapPathContainer m_positionData;
private:

  visualsContainer m_visuals; /**< Contains the data for drawing the Map*/
};


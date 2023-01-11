#pragma once
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "InvalidMapException.hpp"
#include "enemies/BigEnemy.hpp"
#include "enemies/Enemy.hpp"
#include "enemies/SmallEnemy.hpp"
#include "tiles/PathTile.hpp"
#include "tiles/Tile.hpp"

using namespace std;

/// @brief Find first PathTile from map
/// @param map 2D tile vector
/// @return first PathTile
inline PathTile* GetFirstPathTile(vector<vector<Tile*>>* map) {
  for (vector<Tile*> row : *map) {
    for (Tile* tile : row) {
      if (tile->GetType() == "path") {
        PathTile* pathTile = static_cast<PathTile*>(tile);
        if (pathTile->GetOrder() == 0) {
          return pathTile;
        }
      }
    }
  }
  throw InvalidMapException();
}

/// @brief Move all enemies forward one tile, and check if gameover
/// @param tile: first PathTile in map
/// @param enemy New enemy that is added to map, if recursion is called first
/// time.
/// @return true if gameover
inline bool MoveEnemiesAndCheckGameover(PathTile* tile,
                                        Enemy* enemy = nullptr) {
  if (tile->GetNextPathTile() == nullptr) {
    if (enemy != nullptr) {
      // GAMEOVER, enemy reached the last tile
      tile->SetEnemy(enemy);
      return true;
    }
    return false;
  }

  bool isGameover =
      MoveEnemiesAndCheckGameover(tile->GetNextPathTile(), tile->GetEnemy());
  tile->SetEnemy(enemy);
  return isGameover;
}

/// @brief Checks if all enemies are died
/// @param firstPathTile
/// @return boolean
inline bool CheckIfAllEnemiesDied(PathTile* firstPathTile) {
  PathTile* tile = firstPathTile;
  while (tile->GetNextPathTile() != nullptr) {
    if (tile->GetEnemy() != nullptr) {
      return false;
    }
    tile = tile->GetNextPathTile();
  }
  return true;
}

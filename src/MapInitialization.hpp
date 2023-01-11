#pragma once
#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "InvalidMapException.hpp"
#include "InvalidWaveException.hpp"
#include "enemies/BigEnemy.hpp"
#include "enemies/BossEnemy.hpp"
#include "enemies/FinalBossEnemy.hpp"
#include "enemies/SmallEnemy.hpp"
#include "enemies/SplitterEnemy.hpp"
#include "tiles/EmptyTile.hpp"
#include "tiles/PathTile.hpp"
#include "tiles/Tile.hpp"
#include "tiles/TowerTile.hpp"

using namespace std;

/// @brief Splits a string into vector using a character as the split
/// delimiter.
/// @param s String to split
/// @param c: The delimeter char
/// @return vector of strings
inline vector<string> SplitString(string s, char c) {
  stringstream str(s);
  string segment;
  vector<string> segList;
  while (getline(str, segment, c)) {
    segList.push_back(segment);
  }
  return segList;
}

/// @brief Prints vector of strings. Useful for debugging.
/// @param strings
inline void PrintVector(vector<string> strings) {
  cout << "[ ";
  for (string s : strings) {
    cout << s << ", ";
  }
  cout << "]" << endl;
}

/// @brief Prints vector of tiles. Useful for debugging.
/// @param tiles: tile pointers in vector
inline void PrintVector(vector<Tile*>* tiles) {
  cout << "Tile vector: [" << endl;
  for (Tile* tile : *tiles) {
    cout << "  " << *tile << "," << endl;
  }
  cout << "]" << endl;
}
/// @brief Prints vector of path tiles (not in order). Useful for debugging.
/// @param tiles: tile pointers in vector
inline void PrintVector(vector<PathTile*>* tiles) {
  cout << "Path tiles: [" << endl;
  for (Tile* tile : *tiles) {
    cout << "  " << *tile << "," << endl;
  }
  cout << "]" << endl;
}

/// @brief Prints vector of enemies. Useful for debugging.
/// @param enemies: tile pointers in vector
inline void PrintVector(vector<Enemy*>* enemies) {
  cout << "Enemy wave: [" << endl;
  for (Enemy* enemy : *enemies) {
    cout << "  " << *enemy << "," << endl;
  }
  cout << "]" << endl;
}

/// @brief Create new pointer to correct Tile class
/// @param type: abbreviation of tile types ("e", "t" or digit as path)
/// @return Tile*
inline Tile* GetTilePtr(string type) {
  if (type == "e") {
    return new EmptyTile();
  } else if (type == "t") {
    return new TowerTile();
  } else {
    size_t order = 0;
    if (1 == sscanf(type.c_str(), "%zu", &order)) {
      return new PathTile(order);
    }
  }
  return nullptr;
}

/// @brief Create new pointer to correct Enemy class
/// @param type: abbreviation of enemy types ("s", "b" or 'sp)
/// @return Enemy*
inline Enemy* GetEnemyPtr(string type) {
  if (type == "s") {
    return new SmallEnemy();
  } else if (type == "b") {
    return new BigEnemy();
  } else if (type == "sp") {
    return new SplitterEnemy();
  } else if (type == "m") {
    return new BossEnemy();
  } else if (type == "f") {
    return new FinalBoss();
  }
  return nullptr;
}

/// @brief Creates the "doubly linked list" between pathTiles.
/// @param pathTiles: vector<PathTiles*>*
/// @return true if success, otherwise false
inline bool CreateConnectionsInPathTiles(vector<PathTile*>* pathTiles) {
  if ((*pathTiles).size() == 0) {
    return false;
  }
  // sort pathTiles by order
  sort(begin(*pathTiles), end(*pathTiles), [](PathTile* p1, PathTile* p2) {
    return p1->GetOrder() < p2->GetOrder();
  });

  for (int i = 0; i < (int)(*pathTiles).size(); i++) {
    // check that paths are in right order
    if ((int)(*pathTiles)[i]->GetOrder() == i) {
      if (i + 1 < (int)(*pathTiles).size()) {
        if ((int)(*pathTiles)[i + 1]->GetOrder() != i + 1) {
          // invalid path
          return false;
        }
        (*pathTiles)[i]->SetNextPathTile((*pathTiles)[i + 1]);
      }
      if (i - 1 >= 0) (*pathTiles)[i]->SetPrevoiusPathTile((*pathTiles)[i - 1]);

    } else {
      // invalid path
      return false;
    }
  }

  // //   Check that connecting went correctly
  // PathTile* tile = (*pathTiles)[0];
  // while (tile->GetNextPathTile() != nullptr) {
  //   tile = tile->GetNextPathTile();
  // }
  // cout << *tile << endl;

  return true;
}

/// @brief Checks that map is valid and PathTiles are next to each other in
/// order and map's rows are all same size. NOTICE!! that
/// CreateConnectionsInPathTiles() -method must be called before for this to
/// work correctly
/// @param map 2D tile vector
/// @return true if path is valid
inline bool MapIsValid(vector<vector<Tile*>>* map) {
  if ((*map).size() == 0 || (*map)[0].size() == 0) {
    return false;
  }
  for (int row = 0; row < (int)((*map).size()); row++) {
    for (int col = 0; col < (int)((*map)[row].size()); col++) {
      if ((*map)[row][col]->GetType() == "path") {
        PathTile* currentTile = static_cast<PathTile*>((*map)[row][col]);
        if (currentTile->GetNextPathTile() == nullptr) {
          // tile was last tile. No following paths
          continue;
        }

        // check that the current PathTile has the following PathTile next to
        // it
        if ((row - 1) >= 0) {
          if ((*map)[row - 1][col]->GetType() == "path") {
            PathTile* nextTile = static_cast<PathTile*>((*map)[row - 1][col]);
            if (currentTile->GetOrder() + 1 == nextTile->GetOrder()) {
              // following PathTile is on the up.
              // continue checking other tiles
              continue;
            }
          }
        }

        if ((col + 1) < (int)((*map)[row].size())) {
          if ((*map)[row][col + 1]->GetType() == "path") {
            PathTile* nextTile = static_cast<PathTile*>((*map)[row][col + 1]);
            if (currentTile->GetOrder() + 1 == nextTile->GetOrder()) {
              // following PathTile is on the right.
              // continue checking other tiles
              continue;
            }
          }
        }

        if ((row + 1) < (int)((*map).size())) {
          if ((*map)[row + 1][col]->GetType() == "path") {
            PathTile* nextTile = static_cast<PathTile*>((*map)[row + 1][col]);
            if (currentTile->GetOrder() + 1 == nextTile->GetOrder()) {
              // following PathTile is on the down.
              // continue checking other tiles
              continue;
            }
          }
        }

        if ((col - 1) >= 0) {
          if ((*map)[row][col - 1]->GetType() == "path") {
            PathTile* nextTile = static_cast<PathTile*>((*map)[row][col - 1]);
            if (currentTile->GetOrder() + 1 == nextTile->GetOrder()) {
              // following PathTile is on the left.
              // continue checking other tiles
              continue;
            }
          }
        }
        // the current PathTile doesn't have the following tile next to it.
        // invalid path
        return false;
      }
    }
  }

  // check that the map's rows are all same size
  int size = -1;
  for (vector<Tile*> row : *map) {
    if (size == -1) {
      size = row.size();
      continue;
    }
    if (size != (int)row.size()) {
      // invalid map
      return false;
    }
  }

  return true;
}

/// @brief Generates game map as 2D matrix and enemy waves. Wave enemies are
/// reversed in vector (first enemy is the last element of vector).
/// @param file: path to file
/// @return pair<vector<vector<Tile*>>, vector<vector<Enemy*>>>
inline pair<vector<vector<Tile*>>, vector<vector<Enemy*>>> GenerateMapAndWaves(
    string file) {
  vector<vector<Tile*>> map;
  vector<PathTile*> pathTiles;
  vector<vector<Enemy*>> waves;
  bool creatingWaves = false;

  ifstream istr(file);
  if (istr.rdstate() & (istr.failbit | istr.badbit)) {
    // output error to stderr stream
    cerr << "Failed to open file: " << file << endl;
  } else {
    size_t row = 0;
    while (!istr.eof()) {
      string line;
      getline(istr, line);

      if (line == "Waves:") {
        creatingWaves = true;
        row = 0;
        continue;
      } else if (line == "Map:") {
        creatingWaves = false;
        row = 0;
        continue;
      }

      if (creatingWaves) {
        vector<string> parts = SplitString(line, ':');
        if (parts.size() != 2) {
          throw InvalidWaveException();
        }

        vector<string> enemies = SplitString(parts[1], ',');
        // create new wave
        waves.push_back({});
        for (int i = enemies.size() - 1; i >= 0; i--) {
          Enemy* enemy = GetEnemyPtr(enemies[i]);
          if (enemy == nullptr) {
            throw InvalidWaveException();
          }
          // add enemy to wave
          waves[row].push_back(enemy);
        }
      } else {
        // creating map
        vector<string> parts = SplitString(line, ',');
        // add new row to map
        map.push_back({});
        for (string part : parts) {
          // add new column and Tile to it
          Tile* tile = GetTilePtr(part);
          if (tile == nullptr) {
            // invalid character in file
            throw InvalidMapException();
          }
          map[row].push_back(tile);

          if (tile->GetType() == "path") {
            // Add PathTile to pathTiles -vector.
            // pathTiles -vector is used later to order paths.
            PathTile* pathTile = static_cast<PathTile*>(tile);
            pathTiles.push_back(pathTile);
          }
        }
      }
      row++;
    }
  }

  if (!CreateConnectionsInPathTiles(&pathTiles) || !MapIsValid(&map)) {
    throw InvalidMapException();
  }

  if (waves.size() == 0) {
    throw InvalidWaveException();
  }

  pair<vector<vector<Tile*>>, vector<vector<Enemy*>>> mapAndWaves(map, waves);
  return mapAndWaves;
}

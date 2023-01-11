#pragma once
#include <algorithm>

#include "tower.hpp"

class King : public Tower {
 public:
  King(int x, int y, std::vector<std::vector<Tile *>> *level);
  ~King();

  std::pair<int, Tile *> Shoot();
  static int GetPrice();
  void GetTargetTiles(std::vector<std::vector<Tile *>> *);
  std::vector<PathTile *> TileRecurring(
      int x, int y, std::vector<PathTile *> tiles, int range,
      std::vector<std::vector<Tile *>> *level);
  std::vector<Tile *> GetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level);
  static std::vector<Tile *> StaticGetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level, int x, int y);
  static std::vector<Tile *> AllTileRecurring(
      int x, int y, std::vector<Tile *> tiles, int range,
      std::vector<std::vector<Tile *>> *level);
};
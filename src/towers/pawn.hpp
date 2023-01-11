#pragma once
#include <algorithm>

#include "tower.hpp"

class Pawn : public Tower {
 public:
  Pawn(int x, int y, std::vector<std::vector<Tile *>> *level);
  ~Pawn();

  std::pair<int, Tile *> Shoot();
  static int GetPrice();
  void GetTargetTiles(std::vector<std::vector<Tile *>> *);
  std::vector<Tile *> GetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level);
  static std::vector<Tile *> StaticGetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level, int x, int y);
};

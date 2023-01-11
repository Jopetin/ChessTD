#pragma once
#include "tower.hpp"

class Rook : public Tower {
 public:
  Rook(int x, int y, std::vector<std::vector<Tile *>> *level);
  ~Rook();

  enum directions { all, up, down, left, right };
  static int GetPrice();
  std::pair<int, Tile *> Shoot();
  void GetTargetTiles(std::vector<std::vector<Tile *>> *);
  std::vector<PathTile *> TileRecurring(int x, int y,
                                        std::vector<PathTile *> tiles,
                                        int range,
                                        std::vector<std::vector<Tile *>> *level,
                                        directions direction);
  std::vector<Tile *> GetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level);
  static std::vector<Tile *> StaticGetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level, int x, int y);
  static std::vector<Tile *> AllTileRecurring(
      int x, int y, std::vector<Tile *> tiles, int range,
      std::vector<std::vector<Tile *>> *level, directions direction);
};
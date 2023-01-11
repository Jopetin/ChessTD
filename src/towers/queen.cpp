#include "queen.hpp"

std::vector<std::tuple<int, upgradeType, int>> upgradeTableQueen{
    {250, range, 2}, {500, damage, 2}, {300, speed, 5}};

Queen::Queen(int x, int y, std::vector<std::vector<Tile*>>* level)
    : Tower("Queen", 6, 2, 5, 700, x, y, upgradeTableQueen) {
  GetTargetTiles(level);
}

Queen::~Queen() {}

int Queen::GetPrice() { return 700; };

std::pair<int, Tile*> Queen::Shoot() {
  if (coolDown_ <= 0) {
    for (auto* tile : canSee_) {
      if (tile->GetEnemy() != nullptr) {
        coolDown_ = 10;
        return {tile->AttackEnemy(damage_), tile};
      }
    }
    return {0, nullptr};
  } else {
    coolDown_ -= speed_;
    return {0, nullptr};
  }
}

void Queen::GetTargetTiles(std::vector<std::vector<Tile*>>* level) {
  std::vector<PathTile*> sees = TileRecurring(x_, y_, {}, range_, level);
  std::sort(sees.begin(), sees.end(),
            [](PathTile* const& a, PathTile* const& b) -> bool {
              return a->GetOrder() > b->GetOrder();
            });
  canSee_ = sees;
}

std::vector<PathTile*> Queen::TileRecurring(
    int x, int y, std::vector<PathTile*> tiles, int range,
    std::vector<std::vector<Tile*>>* level) {
  if (x >= 0 && x < (int)level->at(0).size() && y >= 0 &&
      y < (int)level->size()) {
    Tile* tile = (*level)[y][x];
    if (tile != nullptr && tile->GetType() == "path") {
      if (std::find(tiles.begin(), tiles.end(), static_cast<PathTile*>(tile)) ==
          tiles.end()) {
        tiles.push_back(static_cast<PathTile*>(tile));
      }
    }
    if (range < 1) {
      return tiles;
    }
    tiles = Queen::TileRecurring(x + 1, y, tiles, range - 1, level);
    tiles = Queen::TileRecurring(x - 1, y, tiles, range - 1, level);
    tiles = Queen::TileRecurring(x, y - 1, tiles, range - 1, level);
    tiles = Queen::TileRecurring(x, y + 1, tiles, range - 1, level);
  }
  return tiles;
}

std::vector<Tile*> Queen::GetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level) {
  return AllTileRecurring(x_, y_, {}, range_, level);
}

std::vector<Tile*> Queen::StaticGetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level, int x, int y) {
  return AllTileRecurring(x, y, {}, 5, level);
}

std::vector<Tile*> Queen::AllTileRecurring(
    int x, int y, std::vector<Tile*> tiles, int range,
    std::vector<std::vector<Tile*>>* level) {
  if (x >= 0 && x < (int)level->at(0).size() && y >= 0 &&
      y < (int)level->size()) {
    Tile* tile = (*level)[y][x];
    if (tile != nullptr) {
      if (std::find(tiles.begin(), tiles.end(), tile) == tiles.end()) {
        tiles.push_back(tile);
      }
    }
    if (range < 1) {
      return tiles;
    }
    tiles = Queen::AllTileRecurring(x + 1, y, tiles, range - 1, level);
    tiles = Queen::AllTileRecurring(x - 1, y, tiles, range - 1, level);
    tiles = Queen::AllTileRecurring(x, y - 1, tiles, range - 1, level);
    tiles = Queen::AllTileRecurring(x, y + 1, tiles, range - 1, level);
  }
  return tiles;
}
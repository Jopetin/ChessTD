#include "king.hpp"

std::vector<std::tuple<int, upgradeType, int>> upgradeTableKing{
    {100, range, 1}, {200, damage, 1}, {300, speed, 3}};

King::King(int x, int y, std::vector<std::vector<Tile*>>* level)
    : Tower("King", 3, 2, 1, 300, x, y, upgradeTableKing) {
  GetTargetTiles(level);
}

King::~King() {}

int King::GetPrice() { return 300; };

std::pair<int, Tile*> King::Shoot() {
  if (coolDown_ <= 0) {
    for (auto* tile : canSee_) {
      if (tile->GetEnemy() != nullptr) {
        coolDown_ = 10;
        return {2 * tile->AttackEnemy(damage_), tile};
      }
    }
    return {0, nullptr};
  } else {
    coolDown_ -= speed_;
    return {0, nullptr};
  }
}

void King::GetTargetTiles(std::vector<std::vector<Tile*>>* level) {
  std::vector<PathTile*> sees = TileRecurring(x_, y_, {}, range_, level);
  std::sort(sees.begin(), sees.end(),
            [](PathTile* const& a, PathTile* const& b) -> bool {
              return a->GetOrder() > b->GetOrder();
            });
  canSee_ = sees;
}

std::vector<PathTile*> King::TileRecurring(
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
    tiles = King::TileRecurring(x + 1, y, tiles, range - 1, level);
    tiles = King::TileRecurring(x - 1, y, tiles, range - 1, level);
    tiles = King::TileRecurring(x, y - 1, tiles, range - 1, level);
    tiles = King::TileRecurring(x, y + 1, tiles, range - 1, level);
  }
  return tiles;
}
std::vector<Tile*> King::GetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level) {
  return AllTileRecurring(x_, y_, {}, range_, level);
}

std::vector<Tile*> King::StaticGetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level, int x, int y) {
  return AllTileRecurring(x, y, {}, 1, level);
}

std::vector<Tile*> King::AllTileRecurring(
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
    tiles = King::AllTileRecurring(x + 1, y, tiles, range - 1, level);
    tiles = King::AllTileRecurring(x - 1, y, tiles, range - 1, level);
    tiles = King::AllTileRecurring(x, y - 1, tiles, range - 1, level);
    tiles = King::AllTileRecurring(x, y + 1, tiles, range - 1, level);
  }
  return tiles;
}



#include "rook.hpp"

#include "../tiles/PathTile.hpp"

std::vector<std::tuple<int, upgradeType, int>> upgradeTableRook{
    {50, range, 1}, {150, damage, 5}, {400, speed, 3}};

Rook::Rook(int x, int y, std::vector<std::vector<Tile*>>* level)
    : Tower("Rook", 2, 10, 3, 500, x, y, upgradeTableRook) {
  GetTargetTiles(level);
}
Rook::~Rook() {}

int Rook::GetPrice() { return 500; };

void Rook::GetTargetTiles(std::vector<std::vector<Tile*>>* level) {
  std::vector<PathTile*> sees = TileRecurring(x_, y_, {}, range_, level, all);
  std::sort(sees.begin(), sees.end(),
            [](PathTile* const& a, PathTile* const& b) -> bool {
              return a->GetOrder() > b->GetOrder();
            });
  canSee_ = sees;
}

/// @brief Gets all path tiles in diagonal directions.
/// @param x x of the tile searching
/// @param y y of the tile searching
/// @param tiles currently found tiles
/// @param range range left for the search
/// @param level level where we are searching
/// @param direction the cardinal direction where we are searching, first time
/// all
/// @return returns tiles.
std::vector<PathTile*> Rook::TileRecurring(
    int x, int y, std::vector<PathTile*> tiles, int range,
    std::vector<std::vector<Tile*>>* level, directions direction) {
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
    switch (direction) {
      case up:
        tiles = Rook::TileRecurring(x, y - 1, tiles, range - 1, level, up);
        break;
      case down:
        tiles = Rook::TileRecurring(x, y + 1, tiles, range - 1, level, down);
        break;
      case left:
        tiles = Rook::TileRecurring(x - 1, y, tiles, range - 1, level, left);
        break;
      case right:
        tiles = Rook::TileRecurring(x + 1, y, tiles, range - 1, level, right);
        break;
      default:
        tiles = Rook::TileRecurring(x + 1, y, tiles, range - 1, level, right);
        tiles = Rook::TileRecurring(x - 1, y, tiles, range - 1, level, left);
        tiles = Rook::TileRecurring(x, y - 1, tiles, range - 1, level, up);
        tiles = Rook::TileRecurring(x, y + 1, tiles, range - 1, level, down);
        break;
    }
  }
  return tiles;
}

std::vector<Tile*> Rook::GetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level) {
  return AllTileRecurring(x_, y_, {}, range_, level, all);
}

std::vector<Tile*> Rook::StaticGetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level, int x, int y) {
  return AllTileRecurring(x, y, {}, 3, level, all);
}

/// @brief Gets all tiles in diagonal directions.
/// @param x x of the tile searching
/// @param y y of the tile searching
/// @param tiles currently found tiles
/// @param range range left for the search
/// @param level level where we are searching
/// @param direction the cardinal direction where we are searching, first time
/// all
/// @return returns tiles.
std::vector<Tile*> Rook::AllTileRecurring(
    int x, int y, std::vector<Tile*> tiles, int range,
    std::vector<std::vector<Tile*>>* level, directions direction) {
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
    switch (direction) {
      case up:
        tiles = Rook::AllTileRecurring(x, y - 1, tiles, range - 1, level, up);
        break;
      case down:
        tiles = Rook::AllTileRecurring(x, y + 1, tiles, range - 1, level, down);
        break;
      case left:
        tiles = Rook::AllTileRecurring(x - 1, y, tiles, range - 1, level, left);
        break;
      case right:
        tiles =
            Rook::AllTileRecurring(x + 1, y, tiles, range - 1, level, right);
        break;
      default:
        tiles =
            Rook::AllTileRecurring(x + 1, y, tiles, range - 1, level, right);
        tiles = Rook::AllTileRecurring(x - 1, y, tiles, range - 1, level, left);
        tiles = Rook::AllTileRecurring(x, y - 1, tiles, range - 1, level, up);
        tiles = Rook::AllTileRecurring(x, y + 1, tiles, range - 1, level, down);
        break;
    }
  }
  return tiles;
}

/// @brief shoots at the enemy with most hp
std::pair<int, Tile*> Rook::Shoot() {
  if (coolDown_ <= 0) {
    PathTile* largest = nullptr;
    for (auto* tile : canSee_) {
      if (tile->GetEnemy() != nullptr) {
        if (largest == nullptr ||
            largest->GetEnemy()->GetHealth() < tile->GetEnemy()->GetHealth()) {
          largest = tile;
        }
      }
    }
    if (largest != nullptr) {
      coolDown_ = 10;
      return {largest->AttackEnemy(damage_), largest};
    } else {
      return {0, nullptr};
    }
  } else {
    coolDown_ -= speed_;
    return {0, nullptr};
  }
}
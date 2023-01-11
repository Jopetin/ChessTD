#include "pawn.hpp"

std::vector<std::tuple<int, upgradeType, int>> upgradeTablePawn{
    {50, speed, 1}, {100, damage, 1}, {200, speed, 2}};

Pawn::Pawn(int x, int y, std::vector<std::vector<Tile*>>* level)
    : Tower("Pawn", 3, 1, 1, 100, x, y, upgradeTablePawn) {
  GetTargetTiles(level);
}

Pawn::~Pawn() {}

int Pawn::GetPrice() { return 100; };

void Pawn::GetTargetTiles(std::vector<std::vector<Tile*>>* level) {
  std::vector<PathTile*> sees;
  int y = y_ + 1;
  int x = x_ + 1;
  int round = 0;
  while (round < 4) {
    if (x >= 0 && x < (int)level->at(0).size() && y >= 0 &&
        y < (int)level->size()) {
      Tile* tile = (*level)[y][x];
      if (tile != nullptr && tile->GetType() == "path") {
        sees.push_back(static_cast<PathTile*>(tile));
      }
    }
    round++;
    switch (round) {
      case 1:
        x -= 2;
        break;
      case 2:
        y -= 2;
        break;
      case 3:
        x += 2;
        break;
      default:
        break;
    }
  }
  std::sort(sees.begin(), sees.end(),
            [](PathTile* const& a, PathTile* const& b) -> bool {
              return a->GetOrder() > b->GetOrder();
            });
  canSee_ = sees;
}

std::vector<Tile*> Pawn::StaticGetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level, int xs, int ys) {
  std::vector<Tile*> sees;
  int y = ys + 1;
  int x = xs + 1;
  int round = 0;
  while (round < 4) {
    if (x >= 0 && x < (int)level->at(0).size() && y >= 0 &&
        y < (int)level->size()) {
      Tile* tile = (*level)[y][x];
      if (tile != nullptr) {
        sees.push_back(tile);
      }
    }
    round++;
    switch (round) {
      case 1:
        x -= 2;
        break;
      case 2:
        y -= 2;
        break;
      case 3:
        x += 2;
        break;
      default:
        break;
    }
  }
  return sees;
}

std::vector<Tile*> Pawn::GetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level) {
  std::vector<Tile*> sees;
  int y = y_ + 1;
  int x = x_ + 1;
  int round = 0;
  while (round < 4) {
    if (x >= 0 && x < (int)level->at(0).size() && y >= 0 &&
        y < (int)level->size()) {
      Tile* tile = (*level)[y][x];
      if (tile != nullptr) {
        sees.push_back(tile);
      }
    }
    round++;
    switch (round) {
      case 1:
        x -= 2;
        break;
      case 2:
        y -= 2;
        break;
      case 3:
        x += 2;
        break;
      default:
        break;
    }
  }
  return sees;
}
std::pair<int, Tile*> Pawn::Shoot() {
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
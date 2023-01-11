#include "tower.hpp"

Tower::Tower(std::string type, int speed, int damage, int range, int price,
             int x, int y,
             std::vector<std::tuple<int, upgradeType, int>>& upgradeTable)
    : type_(type),
      speed_(speed),
      damage_(damage),
      range_(range),
      level_(0),
      coolDown_(0),
      price_(price),
      x_(x),
      y_(y),
      upgradeTable_(upgradeTable) {}

Tower::~Tower() {}

void Tower::GetTargetTiles(std::vector<std::vector<Tile*>>* level) {}

std::vector<Tile*> Tower::GetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level) {}

std::vector<Tile*> Tower::StaticGetAllTargetTiles(
    std::vector<std::vector<Tile*>>* level, int x, int y) {}

std::pair<int, Tile*> Tower::Shoot() {}

std::string Tower::GetType() const { return type_; }

int Tower::GetSpeed() const { return speed_; }

int Tower::GetDamage() const { return damage_; }

int Tower::GetRange() const { return range_; }

int Tower::GetPrice() { return 0; }

int Tower::GetLevel() const { return level_; }

std::tuple<int, upgradeType, int> Tower::GetNextUpgrade() const {
  if (level_ < (int)(upgradeTable_.size())) {
    return upgradeTable_[level_];
  } else {
    return {-1, damage, 0};
  }
}

bool Tower::Upgrade(int money, std::vector<std::vector<Tile*>>* level) {
  int price = std::get<0>(upgradeTable_[level_]);
  upgradeType type = std::get<1>(upgradeTable_[level_]);
  int increase = std::get<2>(upgradeTable_[level_]);
  if (price < 0 || price > money) {
    return false;
  } else {
    switch (type) {
      case speed:
        speed_ += increase;
        level_ += 1;
        break;
      case damage:
        damage_ += increase;
        level_ += 1;
        break;
      case range:
        range_ += increase;
        level_ += 1;
        GetTargetTiles(level);
        break;
      default:
        return false;
    }
    return true;
  }
}

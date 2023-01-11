#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "../tiles/PathTile.hpp"
#include "../tiles/Tile.hpp"
/// @brief All the possible types of upgrades
enum upgradeType { speed, damage, range };

class Tower {
 public:
  Tower(std::string type, int speed, int damage, int range, int price, int x,
        int y, std::vector<std::tuple<int, upgradeType, int>> &upgradeTable);

  virtual ~Tower();

  std::string GetType() const;

  int GetSpeed() const;

  int GetDamage() const;

  int GetRange() const;

  static int GetPrice();

  int GetLevel() const;

  std::pair<int, int> getPos() { return std::make_pair(x_, y_); }

  /// @brief Returns the next upgrade level of the tower.
  /// @return Tuple including the price, upgrade type and increase, in this
  /// order. Price is -1 if tower is at max level.
  std::tuple<int, upgradeType, int> GetNextUpgrade() const;

  /// @brief Upgrades the tower to the next level if possible.
  /// @param money The money the player has. \n HOX! This method does not change
  /// the amount of money the player has, should be handled by gamestate!
  /// @return Returns true if the upgrade was successful. Otherwise returns
  /// false
  ///
  bool Upgrade(int money, std::vector<std::vector<Tile *>> *level);

  /// @brief Shoots at enemies. Done damage and cooldown after attack is done
  /// internally, so this method can be called anytime.
  virtual std::pair<int, Tile *> Shoot();

  /// @brief Gets all the path tiles where the tower can shoot, and adds them to
  /// canSee_, in descending order. Takes no input and returns nothing.
  /// @param level The level where the tiles are
  virtual void GetTargetTiles(std::vector<std::vector<Tile *>> *level);

  /// @brief Gets all the tiles where the tower can shoot, and returns them.
  /// @param level The level where the tiles are
  /// @return returns vector of Tile* where tower can see
  virtual std::vector<Tile *> GetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level);

  /// @brief Statically gets all the tiles where the tower can shoot, and
  /// returns them
  /// @param level Level where tiles are
  /// @param x x of the tower
  /// @param y y of the tower
  /// @return returns vector of Tile* where tower can see
  static std::vector<Tile *> StaticGetAllTargetTiles(
      std::vector<std::vector<Tile *>> *level, int x, int y);

  friend std::ostream &operator<<(std::ostream &stream, Tower &tower) {
    stream << "Tower: " << tower.type_ << "\nAttack speed: " << tower.speed_
           << "\nRange: " << tower.range_
           << "\nDamage per shot: " << tower.damage_
           << "\nLevel: " << tower.level_ << std::endl;
    return stream;
  };

 protected:
  std::string type_;
  int speed_;
  int damage_;
  int range_;
  int level_;
  int coolDown_;
  int price_;
  int x_;
  int y_;
  std::vector<PathTile *> canSee_;
  std::vector<std::tuple<int, upgradeType, int>> &upgradeTable_;
};

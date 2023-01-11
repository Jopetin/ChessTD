#include "PathTile.hpp"

#include <iostream>

#include "enemies/SplitterEnemy.hpp"

/// @brief PathTile class constructor. PathTile inherits the Tile class. This
/// class represents a path on the map.
/// @param order The order number of this tile
/// @param nextPathTile Pointer to next PathTile
/// @param previousPathTilePointer to previous PathTile
PathTile::PathTile(size_t order, PathTile* nextPathTile,
                   PathTile* previousPathTile)
    : Tile("path"),
      order_(order),
      enemy_(nullptr),
      nextPathTile_(nextPathTile),
      previousPathTile_(previousPathTile) {}

/// @brief PathTile destructor
PathTile::~PathTile() {
  if (this->enemy_ != nullptr) {
    delete enemy_;
  }
  // nextPathTile_ and previousPathTile_ should be deleted somewhere else
}

/// @brief Get the tile's order number
/// @return size_t
size_t PathTile::GetOrder() const { return order_; }

/// @brief Get the current enemy, that is on this PathTile
/// @return Pointer to enemy
Enemy* PathTile::GetEnemy() const { return enemy_; }

/// @brief Get the next PathTile
/// @return Pointer to PathTile
PathTile* PathTile::GetNextPathTile() const { return nextPathTile_; }

/// @brief Get the previous PathTile
/// @return Pointer to PathTile
PathTile* PathTile::GetPreviousPathTile() const { return previousPathTile_; }

/// @brief Add enemy on this PathTile
/// @param enemy Pointer to enemy
void PathTile::SetEnemy(Enemy* enemy) { enemy_ = enemy; }

/// @brief Set next PathTile
/// @param pathTile Pointer to PathTile
void PathTile::SetNextPathTile(PathTile* pathTile) { nextPathTile_ = pathTile; }

/// @brief Set previous PathTile
/// @param pathTile Pointer to PathTile
void PathTile::SetPrevoiusPathTile(PathTile* pathTile) {
  previousPathTile_ = pathTile;
}

/// @brief Print PathTile info to terminal
/// @param out ostream
void PathTile::Print(std::ostream& out) const {
  out << "Tile type: " << GetType() << " #" << GetOrder()
      << ", enemy in tile: ";
  if (enemy_ == nullptr) {
    out << "none";
  } else {
    out << *enemy_;
  }
}

/// @brief Attack enemy. If its HP changes to 0 or less, kill the enemy.
/// @param damage
/// @return return enemy reward if it dies, else 0
size_t PathTile::AttackEnemy(size_t damage) {
  enemy_->GetHit(damage);
  if (enemy_->GetHealth() < 1) {
    size_t reward = enemy_->GetReward();
    if (enemy_->GetType() == "Splitter") {
      SplitterEnemy* splitter = static_cast<SplitterEnemy*>(enemy_);
      splitter->Split(this, this->GetPreviousPathTile());
    } else {
      delete enemy_;
      enemy_ = nullptr;
    }
    return reward;
  }
  return 0;
}

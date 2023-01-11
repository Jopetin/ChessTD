#include "SplitterEnemy.hpp"
/// @brief SplitterEnemy class constructor. SplitterEnemy inherits the Enemy
/// class.
SplitterEnemy::SplitterEnemy() : Enemy("Splitter", 2, 15) {}

/// @brief SplitterEnemy class destructor
SplitterEnemy::~SplitterEnemy() {}

/// @brief if Splitter dies, it spawns two small enemies in the previous and own
/// tile.
/// @param currentTile PathTile*
/// @param previousTile PathTile*
void SplitterEnemy::Split(PathTile* currentTile, PathTile* previousTile) {
  if (currentTile != nullptr) {
    currentTile->SetEnemy(new SmallEnemy());
  }
  if (previousTile != nullptr) {
    previousTile->SetEnemy(new SmallEnemy());
  }
}

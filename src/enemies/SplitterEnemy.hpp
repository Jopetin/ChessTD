#pragma once
#include "../tiles/PathTile.hpp"
#include "Enemy.hpp"
#include "../enemies/SmallEnemy.hpp"

class SplitterEnemy : public Enemy {
 public:
  SplitterEnemy();
  ~SplitterEnemy();

  void Split(PathTile* currentTile, PathTile* previousTile);
};
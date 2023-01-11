#pragma once
#include "EmptyTile.hpp"
#include "Tile.hpp"
#include "src/towers/rook.hpp"

class TowerTile : public Tile {
 public:
  TowerTile();
  ~TowerTile();

  Tower* GetTower() { return tower_; }

  void SetTower(Tower* tower) { tower_ = tower; }

 protected:
  virtual void Print(std::ostream& out) const;

 private:
  Tower* tower_;
};

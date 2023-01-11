#pragma once
#include "../enemies/Enemy.hpp"
#include "Tile.hpp"

class PathTile : public Tile {
 public:
  PathTile(size_t order, PathTile* nextPathTile = nullptr,
           PathTile* previousPathTile = nullptr);
  ~PathTile();

  size_t GetOrder() const;
  Enemy* GetEnemy() const;
  PathTile* GetNextPathTile() const;
  PathTile* GetPreviousPathTile() const;

  void SetEnemy(Enemy* enemy);
  void SetNextPathTile(PathTile* pathTile);
  void SetPrevoiusPathTile(PathTile* pathTile);

  size_t AttackEnemy(size_t damage);

 protected:
  virtual void Print(std::ostream& out) const;

 private:
  size_t order_;
  Enemy* enemy_;
  PathTile* nextPathTile_;
  PathTile* previousPathTile_;
};
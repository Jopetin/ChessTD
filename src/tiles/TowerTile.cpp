#include "TowerTile.hpp"

/// @brief TowerTile class constructor. TowerTile inherits the Tile
/// class. Represents the towers on the map.
TowerTile::TowerTile() : Tile("tower"), tower_(nullptr) {}

/// @brief TowerTile destructor. Deletes tower pointer.
TowerTile::~TowerTile() {
  if (tower_ != nullptr) {
    delete tower_;
  }
}

/// @brief Print tower info to terminal.
/// @param out ostream
void TowerTile::Print(std::ostream& out) const {
  out << "Tile type: " << GetType() << ", tower in tile: ";
  if (tower_ == nullptr) {
    out << "none";
    ;
  } else {
    out << *tower_;
  }
}

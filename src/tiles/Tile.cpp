#include "Tile.hpp"

/// @brief Tile class constructor. Tile is abstract base class for different tile types
/// @param type "path", "tower" or "empty"
Tile::Tile(const std::string& type) : type_(type) { }

/// @brief Tile class destructor
Tile::~Tile() {}

/// @brief Get the tile type
/// @return "path", "tower" or "empty"
const std::string Tile::GetType() const { return type_; }

/// @brief Print tile to terminal
/// @param out ostream
void Tile::Print(std::ostream& out) const {
  out << "Tile type: " << GetType();
}

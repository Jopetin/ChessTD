#include "EmptyTile.hpp"

/// @brief EmptyTile class constructor. EmptyTile inherits the Tile
/// class. Represents the spots where there is no tower yet on the map.
EmptyTile::EmptyTile() : Tile("empty") {}

/// @brief EmptyTile destructor
EmptyTile::~EmptyTile() {}

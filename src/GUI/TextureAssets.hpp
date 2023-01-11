#pragma once

#include <map>
#include <string>

// Add tower image files here with a sensible key

namespace TDImageFiles {
const std::map<const std::string, const std::string> Textures{
    {"pawn", "../assets/towers/chess-pawn.png"},
    {"king", "../assets/towers/chess-king.png"},
    {"queen", "../assets/towers/chess-queen.png"},
    {"rook", "../assets/towers/chess-rook.png"},
    {"smallEnemy", "../assets/enemies/token.png"},
    {"bigEnemy", "../assets/enemies/meeple.png"},
    {"splitEnemy", "../assets/enemies/two-coins.png"},
    {"bossEnemy", "../assets/enemies/abbot-meeple.png"},
    {"finalBoss", "../assets/enemies/meeple-king.png"},
};
}
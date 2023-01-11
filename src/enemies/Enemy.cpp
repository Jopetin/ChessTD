#include "Enemy.hpp"

/// @brief Enemy class constructor. Enemy is abstract base class for different enemy types.
/// @param type "Small", "Big" or "Splitter"
/// @param health How much health enemy should have
/// @param reward The reward amount when enemy dies
Enemy::Enemy(const std::string& type, int health, const size_t reward)
    : type_(type), health_(health), reward_(reward){};

/// @brief Enemy class destructor
Enemy::~Enemy(){};

/// @brief Get the enemy type
/// @return "Small", "Big" or "Splitter"
const std::string Enemy::GetType() const { return type_; }

/// @brief Get the enemy's current health points
/// @return int
int Enemy::GetHealth() const { return health_; }

/// @brief Get the enemy's reward
/// @return size_t
size_t Enemy::GetReward() const { return reward_; }

/// @brief Reduce the enemy's health
/// @param amount How much damage was dealt to the enemy
void Enemy::GetHit(size_t amount) { health_ -= amount; }

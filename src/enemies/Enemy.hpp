#pragma once
#include <iostream>
#include <string>

class Enemy {
 public:
  Enemy(const std::string& type, int health, size_t reward);

  virtual ~Enemy() = 0;

  const std::string GetType() const;

  int GetHealth() const;

  size_t GetReward() const;

  void GetHit(size_t amount);

  friend std::ostream& operator<<(std::ostream& out, const Enemy& e) {
    out << "Enemy type: " << e.GetType() << ", current HP: " << e.GetHealth()
        << ", " << &e;
    return out;
  }

 private:
  std::string type_;
  int health_;
  const size_t reward_;
};

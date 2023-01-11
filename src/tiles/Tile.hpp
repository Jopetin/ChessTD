#pragma once
#include <iostream>
#include <string>

class Tile {
 public:
  Tile(const std::string& type);
  virtual ~Tile() = 0;

  const std::string GetType() const;

  friend std::ostream& operator<<(std::ostream& o, const Tile& t);

 protected:
  virtual void Print(std::ostream& out) const;

 private:
  const std::string type_;
};

inline std::ostream& operator<<(std::ostream& out, const Tile& t) {  
  t.Print(out);
  return out;
}

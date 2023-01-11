#include <iostream>

#include "EnemyTest.hpp"
#include "GUITest.hpp"
#include "SystemTest.hpp"
#include "TowerTest.hpp"

int main() {
  std::cout << "Starting tests:\n--------------" << std::endl;
  GUITest();
  EnemyTest();
  TowerTest();
  std::cout << "----------------\nAll tests done!" << std::endl;
  return 0;
}
#include "GUITest.hpp"

#include <iostream>

#include "MapInitialization.hpp"

int GUITest() {
  // create map from file
  std::vector<std::vector<Tile*>> map;
  std::vector<std::vector<Enemy*>> waves;
std:
  tie(map, waves) = GenerateMapAndWaves("../src/maps/test_map.txt");

  std::cout << "Starting GUI test..." << std::endl;
  GUI subject = GUI(map[0].size(), map.size(), &map);
  std::cout << "Window created." << std::endl;
  sf::Event event;
  subject.loadTextures();
  subject.updateTiles();
  subject.render();
  while (subject.isRunning()) {
    while (subject.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        subject.close();
      }
    }
  }
  std::cout << "Test over!" << std::endl;

  return 0;
}

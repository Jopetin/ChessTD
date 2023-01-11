#include <iostream>

#include "GUI/GUI.hpp"
#include "src/MapInitialization.hpp"
#include "src/SomeTesting.hpp"

/// @brief Game main loop
/// @param tiles
/// @param waves
/// @return string that tells the status of game level. "win", "gameover" or
/// "quit". Win: the current level/map is cleared, Gameover: enemy got into the
/// last pathTile, Quit: user quitted the game
std::string MainLoop(std::vector<std::vector<Tile*>> tiles,
                     std::vector<std::vector<Enemy*>> waves) {
  std::cout << "Initializing the window" << std::endl;
  PathTile* first = GetFirstPathTile(&tiles);
  std::cout << tiles[0].size() << ":" << tiles.size() << std::endl;
  GUI interface = GUI(30, 20, &tiles);
  std::cout << "Window created, Game starting..." << std::endl;
  sf::Event event;
  sf::Clock gameClock;
  sf::Clock ammoClock;
  size_t current_wave = 0;
  bool spawnEnemy = false;
  int score = 4000;
  int roundscore = 0;
  interface.setScore(score);
  interface.setWave(current_wave + 1);
  std::vector<Tower*> towers;
  bool paused = true;
  bool placingTower = false;
  bool ammoFlying = false;
  interface.updateTiles();
  interface.render();

  while (interface.isRunning()) {
    while (interface.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          // interface.close();
          return "quit";

        case sf::Event::Resized:
          interface.resetSize();
          break;

        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = interface.getMousePos();
            if (interface.checkPauseButtonBounds(pos)) {
              if (paused) {
                paused = false;
                interface.pause(false);
                interface.updateTiles();
                gameClock.restart();
              } else {
                paused = true;
                interface.pause(true);
              }
            } else if (interface.checkTowerButtonBounds(pos)) {
              placingTower = true;
            } else if (interface.checkUpgradeButtonBounds(pos)) {
              interface.upgradeTower(&score);
              interface.loadUpgradeInfo();

            } else if (paused) {
              interface.selectTile();
            }
          }
          break;

        case sf::Event::MouseMoved:
          if (paused && placingTower) {
            interface.selectTile();
          }
          break;

        case sf::Event::MouseButtonReleased:
          if (paused && placingTower) {
            placingTower = false;
            Tower* toweraddition;
            if (interface.release(&toweraddition, &score)) {
              towers.push_back(toweraddition);
            }
            interface.updateTiles();
          }
          break;

        default:
          break;
      }
    }

    if (!paused && gameClock.getElapsedTime() > sf::milliseconds(500)) {
      gameClock.restart();
      Enemy* enemy = nullptr;
      if (waves[current_wave].size() > 0) {
        if (spawnEnemy) {
          // get next enemy to spawn
          enemy = waves[current_wave].back();
          waves[current_wave].pop_back();
        }
        spawnEnemy = !spawnEnemy;
      } else {
        if (CheckIfAllEnemiesDied(first)) {
          // wave ended
          paused = true;
          interface.pause(true);
          spawnEnemy = false;
          current_wave++;
          interface.setWave(current_wave + 1);
          if (current_wave == waves.size()) {
            // interface.close();
            // level passed, all waves cleared
            return "win";
          }
        }
      }

      if (MoveEnemiesAndCheckGameover(first, enemy)) {
        for (std::vector<Enemy*> wave : waves) {
          for (Enemy* e : wave) {
            delete e;
          }
        }

        // interface.close();
        return "gameover";
      }

      interface.updateTiles();

      roundscore = 0;
      for (auto t : towers) {
        auto pos = t->getPos();
        auto results = t->Shoot();
        if (results.second != nullptr) {
          interface.createAmmunition(pos, results.second);
          ammoFlying = true;
          roundscore = roundscore + results.first;
          ammoClock.restart();
        }
      }
    }

    if (ammoFlying && ammoClock.getElapsedTime() > interface.getAmmoTime()) {
      ammoClock.restart();
      if (interface.moveAmmunition()) {
        ammoFlying = false;
        score = score + roundscore;
        interface.setScore(score);
        interface.updateTiles();
      }
    }

    interface.render();
  }
  return "quit";
}

int main() {
  // TODO add new maps here
  std::vector<std::string> mapPaths = {
      "../src/maps/map1.txt", "../src/maps/map2.txt", "../src/maps/map3.txt",
      "../src/maps/map4.txt", "../src/maps/map5.txt"};

  size_t i = 0;
  while (i < mapPaths.size()) {
    // a vector to hold the map
    std::vector<std::vector<Tile*>> tiles;
    std::vector<std::vector<Enemy*>> waves;
    tie(tiles, waves) = GenerateMapAndWaves(mapPaths[i]);

    std::string gameStatus = MainLoop(tiles, waves);

    std::cout << "Game status: " << gameStatus << std::endl;
    if (gameStatus == "win") {
      // open the next map
      i++;
      continue;
    } else if (gameStatus == "gameover") {
      // restart the current map
      continue;
    } else {
      // quit game
      break;
    }
  }

  // all maps won or quitted the game

  std::cout << "Game quit" << std::endl;
  return 0;
}

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <sstream>

#include "TextureAssets.hpp"
#include "src/enemies/BigEnemy.hpp"
#include "src/enemies/BossEnemy.hpp"
#include "src/enemies/FinalBossEnemy.hpp"
#include "src/enemies/Enemy.hpp"
#include "src/enemies/SmallEnemy.hpp"
#include "src/enemies/SplitterEnemy.hpp"
#include "src/tiles/EmptyTile.hpp"
#include "src/tiles/PathTile.hpp"
#include "src/tiles/Tile.hpp"
#include "src/tiles/TowerTile.hpp"
#include "src/towers/king.hpp"
#include "src/towers/pawn.hpp"
#include "src/towers/queen.hpp"
#include "src/towers/rook.hpp"

// size of a tile in pixels
#define TILESIZE 50
// size of an enemy in pixels
#define ENEMYSIZE 40
// width of the ingame menu in pixels
#define MENUWIDTH 200
// amount of animation steps used in the tower firing
#define SHELLSTEPS 15
// amount of time the tower shells are in flight in milliseconds
#define FLIGHTTIME 250

/**
 * @brief Depicts different tile selection modes:
 * @param empty A tower is being held over a tile viable for placement.
 * @param tower A tower tile with a tower is selected.
 * @param none No tile is selected
 *
 */
enum SelectMode { none, empty, tower };

/**
 * @brief Different tower types to tell which one is currently being placed.
 *
 */
enum TowerTypes { NoTower, pawn, king, rook, queen };

class GUI {
 public:
  /**
   * @brief Construct a new GUI::GUI object that represents the base of the
   * graphical user interface. It consists of a tilegrid as well as a menu.
   * @param width the width of the window (in tiles)
   * @param heigth the height of the window (in tiles)
   * @param tiles the tile grid used in game (should match the size parameters given)
   */
  GUI(int width, int height, std::vector<std::vector<Tile*>>* tiles);

  ~GUI() {}

  /**
   * @brief Determinates whether the window is open
   */
  bool isRunning() const { return window_.isOpen(); }

  /**
   * @brief Preloads the textures in TextureAssets.hpp to textures_ for more
   * efficient use
   *
   */
  void loadTextures();

  /**
   * @brief Updates the latest Tile information into the frame.
   * It in practise refreshes the graphical elements to represent the latest state in the game.
   * Since tiles also hold information about the enemies and towers it also updates their position etc.
   *
   */
  void updateTiles();

  /**
   * @brief Create an graphical enemy based on the information in the tile.
   *
   * @param tile The tile in question
   * @return Whether a new enemy was created
   */
  bool createEnemy(PathTile* tile, int row, int column);

  /**
   * @brief Create a graphical Tower based on the information in the tile.
   *  
   * @param tile the tile in question.
   * @return Whether a new tower was created
   */
  bool createTower(TowerTile* tile, int row, int column);

  /**
   * @brief Renders the new frame and displays it in the window. This makes the changes of updateTiles visible to the user.
   * The inner state of the game affects what e.g. menu elements are drawn, as some of them are mutually exclusive.
   */
  void render();

  /**
   * @brief Rezises the window to new values
   *
   *
   */
  void resize(int width, int height);

  /**
   * @brief Resizes the window back to original values.
   * Used to deny user resizing of the window as the SFML standard implementation didn't behave properly.
   */
  void resetSize();

  /**
   * @brief Requests an event from the window and hands it down. 
   * The class by itself doesn't handle events but offers a multitude of methods to help with it.
   *
   */
  bool pollEvent(sf::Event& e);

  /**
   * @brief Closes the window.
   *
   */
  void close() { window_.close(); }

  /**
   * @brief Initializes all of the menu elements (positions, colours etc.).
   * Needs to be called once after initialization and before the first render.
   */
  void initializeMenu();

  /**
   * @brief Sets the game status to paused/unpaused.
   * Pausing affects e.g. what menu elements are drawn to the user.
   *
   * @param isPaused true if pausing the game, false when continuing
   */
  void pause(bool isPaused);

  /**
   * @brief Checks whether a given position is within the pause button.
   * 
   * @param pos position to be checked
   * @return whether it was within the button
   */
  bool checkPauseButtonBounds(sf::Vector2f pos) {
    return pauseButton_.getGlobalBounds().contains(pos);
  }

  /**
   * @brief Checks whether a given position is within any of the tower buttons.
   *  If it is it sets selectedTower_ to reflect which one.
   * 
   * @param pos position to be checked
   * @return whether it was within any of the buttons
   */
  bool checkTowerButtonBounds(sf::Vector2f pos);

  /**
   * @brief Checks whether a given position is within the upgrade button AND a tower is currently selected within the game.
   * 
   * @param pos position to be checked
   * @return whether it was within the button
   */
  bool checkUpgradeButtonBounds(sf::Vector2f pos) {
    if (tileSelectionMode_ == tower) {
      return upgradeButton_.getGlobalBounds().contains(pos);
    }
    return false;
  }

  /**
   * @brief Refreshes the upgrade info text to represent the relevant upgrade
   */
  void loadUpgradeInfo();

  /**
   * @brief Attempts to upgrade the currently selected tower.
   *  Fails if the amount of points available is insufficient.
   *
   * @param score Available points
   * @return Whether the upgrade was successful
   */
  bool upgradeTower(int* score);

  /**
   * @brief Create a graphical shell that flies from the tower to the enemy when shooting. The amount of movement steps taken in the flying animation is
   * set by SHELLSTEPS. The idea is that all of the shells complete their flight before the next game step. Therefore the length of the steps
   * is affected by the distance travelled, so that each shell completes their flight simultaneously.
   * 
   * @param from The towers coords (x, y)
   * @param to The tile where the enemy is
   */
  void createAmmunition(std::pair<int, int> from, Tile* to);

  /**
   * @brief Moves all of the ammunition based on the movement vector stored with
   * them. When their path is finished it destroys the shells.
   *
   * @return Whether the shells reached their target
   */
  bool moveAmmunition();

  /**
   * @brief returns mouse position in local coordinates
   *
   * @return sf::Vector2f
   */
  sf::Vector2f getMousePos() {
    sf::Vector2i pos = sf::Mouse::getPosition(window_);
    return sf::Vector2f(pos.x, pos.y);
  }

  /**
   * @brief Translates a position into a place in the grid if possible
   *
   * @param pos position to be translated
   * @param grid a pointer to a int vector for the result
   * @return true It was possible, the value is now in grid.
   * @return false It wasn't possible, nothing happens.
   */
  bool posAsGrid(sf::Vector2f pos, sf::Vector2i* grid) {
    int x = (int)pos.x / TILESIZE;
    int y = (int)pos.y / TILESIZE;
    if (x >= 0 && x < windowColumns_ && y >= 0 && y < windowRows_) {
      *grid = sf::Vector2i(x, y);
      return true;
    } else {
      return false;
    }
  }

  /**
   * @brief Selects the tile that is currently under the mouse.
   * The effects of the selection are determined by the state of the game, e.g. whether a tower is currently being held.
   * Trying to select a tile while the mouse is off the tile grid does nothing.
   */
  void selectTile();

  /**
   * @brief Fetches the tile according to the vector given.
   * 
   */
  Tile* getTile(sf::Vector2i pos) const {return (*tiles_)[pos.y][pos.x];}

  /**
   * @brief Returns the time needed for a single ammo flight step.
   * 
   * @return time in milliseconds (constant)
   */
  sf::Time getAmmoTime() const {return sf::milliseconds(FLIGHTTIME / SHELLSTEPS);}

  /**
   * @brief Handles the actions connected to releasing the mouse.
   * Places a tower if one is currently being held in a suitable position
   *
   * @param spot a pointer to a spot for the tower pointer to be stored in
   * @param score a pointer to the current available points
   * @return true a tower was placed, the pointer is stored in spot and the score is deducted.
   * @return false a tower was not placed, nothing happens
   */
  bool release(Tower** spot, int* score);

  /**
   * @brief Highlights the given tile with an outline of given color. Calling with an
   * illegal position will cause undefined behaviour. 
   * Should only be used when the position is already confirmed correct, e.g. with the posAsGrid function.
   *
   * @param gridpos the position of the tile in the grid
   */
  void highlight(sf::Vector2i gridpos, sf::Color color);

  /**
   * @brief Highlights the graphical tiles that represent the tiles in the given list with the given color.
   * Calling it with tiles not in the game will cause undefined behaviour.
   * 
   * @param tiles vector of tiles to be highlighted
   */
  void highlight(std::vector<Tile*> tiles, sf::Color color);

  /**
   * @brief Visualizes the currently selected towers range if it was placed in
   * the given position
   *
   * @param gridpos position the tower is placed
   */
  void visualizeRange(sf::Vector2i gridpos);

  /**
   * @brief Sets the score counter to the given value.
   * 
   */
  void setScore(int value) {
    std::stringstream ss;
    ss << "Points: " << value;
    pointCounterText_.setString(ss.str());
  }

  /**
   * @brief Sets the wave counter to the given value.
   * 
   */
  void setWave(int value) {
    std::stringstream ss;
    ss << "Wave: " << value;
    waveCounterText_.setString(ss.str());
  }

 private:
 // variables and flags
  sf::RenderWindow window_;
  int windowColumns_;
  int windowRows_;
  int width_;
  int height_;
  bool paused_;
  int shellcounter_;
  SelectMode tileSelectionMode_;
  TowerTypes selectedTower_;
  Tile* selectedTile_;

  // menu elements
  sf::RectangleShape background_;
  sf::RectangleShape pauseButton_;
  sf::Text pauseButtonText_;
  sf::Font arial_;
  sf::RectangleShape counterBox_;
  sf::Text pointCounterText_;
  sf::Text waveCounterText_;
  sf::RectangleShape towerBox1_;
  sf::Text towerPrice1_;
  sf::RectangleShape towerBox2_;
  sf::Text towerPrice2_;
  sf::RectangleShape towerBox3_;
  sf::Text towerPrice3_;
  sf::RectangleShape towerBox4_;
  sf::Text towerPrice4_;
  sf::RectangleShape upgradeButton_;
  sf::Text upgradeInfo_;
  sf::Text upgradeLabel_;

  // containers
  std::vector<std::vector<Tile*>>* tiles_;
  std::map<Tile*, sf::RectangleShape> guitiles_;
  std::vector<sf::RectangleShape> highlightGuitiles_;
  std::list<sf::RectangleShape> enemies_;
  std::list<sf::RectangleShape> towers_;
  std::map<std::string, sf::Texture> textures_;
  std::map<std::pair<int, int>, sf::RectangleShape> ammo_;
};

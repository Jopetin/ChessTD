#include "GUI.hpp"

#include <random>

class InvalidFontException : public std::exception {
  virtual const char* what() const noexcept { return "Font error"; }
};

GUI::GUI(int width, int heigth, std::vector<std::vector<Tile*>>* tiles)
    : window_(sf::RenderWindow(
          sf::VideoMode(width * TILESIZE + MENUWIDTH, heigth * TILESIZE),
          "ChessTD", sf::Style::Close)) {
  windowColumns_ = width;
  windowRows_ = heigth;
  width_ = width * TILESIZE + MENUWIDTH;
  height_ = heigth * TILESIZE;
  tiles_ = tiles;
  paused_ = true;
  tileSelectionMode_ = none;
  selectedTower_ = NoTower;
  window_.setFramerateLimit(200);
  window_.setPosition(sf::Vector2i(100, 100));
  loadTextures();
  updateTiles();
  initializeMenu();
}

void GUI::loadTextures() {
  for (auto s : TDImageFiles::Textures) {
    sf::Texture texture = sf::Texture();
    texture.loadFromFile(s.second);
    textures_[s.first] = texture;
  }
}

void GUI::updateTiles() {
  // clears the previous graphical tiles and enemies
  guitiles_.clear();
  highlightGuitiles_.clear();
  enemies_.clear();
  towers_.clear();
  // implemented a random element to be used in the grass color pattern
  std::default_random_engine random(69);
  std::uniform_int_distribution nums(-10, 10);

  // builds the graphical tiles based on tile information
  for (int row = 0; row < windowRows_; row++) {
    for (int column = 0; column < windowColumns_; column++) {
      Tile* tile = (*tiles_)[row][column];
      sf::RectangleShape newtile(sf::Vector2f(TILESIZE, TILESIZE));
      //  the position on screen is calculated based on the position in the vector
      newtile.setPosition(sf::Vector2f(float(column * TILESIZE), float(row * TILESIZE)));

      // match the colour based on the tile type
      if (typeid(*tile) == typeid(EmptyTile)) {
        newtile.setFillColor(sf::Color(86, 186 + nums(random), 43));
      } else if (typeid(*tile) == typeid(TowerTile)) {
        newtile.setFillColor(sf::Color(86, 186 + nums(random), 43));

        createTower((TowerTile*)tile, row, column);

      } else if (typeid(*tile) == typeid(PathTile)) {
        newtile.setFillColor(sf::Color(232, 174, 58));

        createEnemy((PathTile*)tile, row, column);

      } else {
        newtile.setFillColor(sf::Color::White);
      }
      guitiles_[tile] = newtile;
    }
  }
}

bool GUI::createEnemy(PathTile* tile, int row, int column) {
  Enemy* enemyp = tile->GetEnemy();
  if (enemyp != nullptr) {
    if (typeid(*enemyp) == typeid(SmallEnemy)) {
      sf::RectangleShape enemy(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      enemy.setTexture(&textures_["smallEnemy"]);  // TODO: Replace "enemy00"
      enemy.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                        row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      enemies_.push_back(enemy);
      return true;

    } else if (typeid(*enemyp) == typeid(BigEnemy)) {
      sf::RectangleShape enemy(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      enemy.setTexture(&textures_["bigEnemy"]);  // TODO: Replace "enemy00"
      enemy.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                        row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      enemies_.push_back(enemy);
      return true;

    } else if (typeid(*enemyp) == typeid(SplitterEnemy)) {
      sf::RectangleShape enemy(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      enemy.setTexture(&textures_["splitEnemy"]);  // TODO: Replace "enemy00"
      enemy.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                        row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      enemies_.push_back(enemy);
      return true;

    } else if (typeid(*enemyp) == typeid(BossEnemy)) {
      sf::RectangleShape enemy(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      enemy.setTexture(&textures_["bossEnemy"]);  // TODO: Replace "enemy00"
      enemy.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                        row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      enemies_.push_back(enemy);
      return true;
    } else if (typeid(*enemyp) == typeid(FinalBoss)) {
      sf::RectangleShape enemy(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      enemy.setTexture(&textures_["finalBoss"]);  // TODO: Replace "enemy00"
      enemy.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                        row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      enemies_.push_back(enemy);
      return true;
    }
  }
  return false;
}

bool GUI::createTower(TowerTile* tile, int row, int column) {
  Tower* towerp = tile->GetTower();
  if (towerp != nullptr) {
    if (typeid(*towerp) == typeid(Rook)) {
      sf::RectangleShape tow(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      tow.setTexture(&textures_["rook"]);
      tow.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                      row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      towers_.push_back(tow);
      return true;
    } else if (typeid(*towerp) == typeid(Pawn)) {
      sf::RectangleShape tow(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      tow.setTexture(&textures_["pawn"]);
      tow.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                      row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      towers_.push_back(tow);
      return true;
    } else if (typeid(*towerp) == typeid(King)) {
      sf::RectangleShape tow(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      tow.setTexture(&textures_["king"]);
      tow.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                      row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      towers_.push_back(tow);
      return true;
    } else if (typeid(*towerp) == typeid(Queen)) {
      sf::RectangleShape tow(sf::Vector2f(ENEMYSIZE, ENEMYSIZE));
      tow.setTexture(&textures_["queen"]);
      tow.setPosition(column * TILESIZE + (TILESIZE - ENEMYSIZE) / 2,
                      row * TILESIZE + (TILESIZE - ENEMYSIZE) / 2);
      towers_.push_back(tow);
      return true;
    }
  }
  return false;
}

// renders the screen, all of the elements should be initialized before this
void GUI::render() {
  window_.clear();
  window_.draw(background_);
  window_.draw(pauseButton_);
  window_.draw(pauseButtonText_);
  window_.draw(counterBox_);
  window_.draw(pointCounterText_);
  window_.draw(waveCounterText_);

  // drw either the tower selection menu or the upgrade menu
  if (paused_) {
    if (tileSelectionMode_ == tower) {
      window_.draw(upgradeButton_);
      window_.draw(upgradeLabel_);
      window_.draw(upgradeInfo_);
    } else {
      window_.draw(towerBox1_);
      window_.draw(towerBox2_);
      window_.draw(towerBox3_);
      window_.draw(towerBox4_);
      window_.draw(towerPrice1_);
      window_.draw(towerPrice2_);
      window_.draw(towerPrice3_);
      window_.draw(towerPrice4_);
    }
  }

  for (auto tile : guitiles_) {
    window_.draw(tile.second);
  }
  for (auto tile : highlightGuitiles_) {
    window_.draw(tile);
  }
  for (auto enemy : enemies_) {
    window_.draw(enemy);
  }
  for (auto tow : towers_) {
    window_.draw(tow);
  }
  for (auto shell : ammo_) {
    window_.draw(shell.second);
  }
  window_.display();
}

bool GUI::pollEvent(sf::Event& e) { return window_.pollEvent(e); }

void GUI::resize(int width, int height) {
  sf::Vector2u size(width, height);
  window_.setSize(size);
}

void GUI::resetSize() { resize(width_, height_); }

void GUI::initializeMenu() {
  // create the background
  background_ = sf::RectangleShape(sf::Vector2f(MENUWIDTH, height_));
  background_.setPosition(sf::Vector2f(width_ - MENUWIDTH, 0));
  background_.setFillColor(sf::Color(222, 219, 210));

  // pause/play button
  pauseButton_ = sf::RectangleShape(sf::Vector2f(MENUWIDTH - 6, 44));
  pauseButton_.setPosition(sf::Vector2f(width_ - MENUWIDTH + 3, 3));
  pauseButton_.setOutlineThickness(3.f);
  pauseButton_.setOutlineColor(sf::Color::Black);
  pauseButton_.setFillColor(sf::Color(233, 118, 91));

  // text for the pause/play button
  if (!arial_.loadFromFile("../src/GUI/arial.ttf")) {
    throw new InvalidFontException;
  } else {
    pauseButtonText_ = sf::Text("Play", arial_, 30);
    pauseButtonText_.setFillColor(sf::Color::Black);
    pauseButtonText_.setPosition(sf::Vector2f(width_ - MENUWIDTH + 20, 5));
  }

  // Point counter
  counterBox_ = sf::RectangleShape(sf::Vector2f(MENUWIDTH, 100));
  counterBox_.setPosition(sf::Vector2f(width_ - MENUWIDTH, 50));
  counterBox_.setFillColor(sf::Color(252, 182, 119));

  // text for the point counter
  pointCounterText_ = sf::Text("", arial_, 30);
  pointCounterText_.setFillColor(sf::Color::Black);
  pointCounterText_.setPosition(sf::Vector2f(width_ - MENUWIDTH + 20, 55));

  // text for the Wave counter
  waveCounterText_ = sf::Text("", arial_, 30);
  waveCounterText_.setFillColor(sf::Color::Black);
  waveCounterText_.setPosition(sf::Vector2f(width_ - MENUWIDTH + 20, 105));

  // box for the first tower type Pawn
  towerBox1_ = sf::RectangleShape(sf::Vector2f(100, 100));
  towerBox1_.setTexture(&textures_["pawn"]);
  towerBox1_.setPosition(sf::Vector2f(width_ - 150, 300));

  // pricetag for the Pawn tower
  towerPrice1_ =
      sf::Text("Price: " + std::to_string(Pawn::GetPrice()), arial_, 20);
  towerPrice1_.setFillColor(sf::Color::Black);
  towerPrice1_.setPosition(sf::Vector2f(width_ - 150, 400));

  // box for the second tower type King
  towerBox2_ = sf::RectangleShape(sf::Vector2f(100, 100));
  towerBox2_.setTexture(&textures_["king"]);
  towerBox2_.setPosition(sf::Vector2f(width_ - 150, 450));

  // pricetag for the King tower
  towerPrice2_ =
      sf::Text("Price: " + std::to_string(King::GetPrice()), arial_, 20);
  towerPrice2_.setFillColor(sf::Color::Black);
  towerPrice2_.setPosition(sf::Vector2f(width_ - 150, 550));

  // box for the third tower type Rook
  towerBox3_ = sf::RectangleShape(sf::Vector2f(100, 100));
  towerBox3_.setTexture(&textures_["rook"]);
  towerBox3_.setPosition(sf::Vector2f(width_ - 150, 600));

  // pricetag for the Rook tower
  towerPrice3_ =
      sf::Text("Price: " + std::to_string(Rook::GetPrice()), arial_, 20);
  towerPrice3_.setFillColor(sf::Color::Black);
  towerPrice3_.setPosition(sf::Vector2f(width_ - 150, 700));

  // box for the fourth tower type Queen
  towerBox4_ = sf::RectangleShape(sf::Vector2f(100, 100));
  towerBox4_.setTexture(&textures_["queen"]);
  towerBox4_.setPosition(sf::Vector2f(width_ - 150, 750));

  // pricetag for the Queen tower
  towerPrice4_ =
      sf::Text("Price: " + std::to_string(Queen::GetPrice()), arial_, 20);
  towerPrice4_.setFillColor(sf::Color::Black);
  towerPrice4_.setPosition(sf::Vector2f(width_ - 150, 850));

  // upgrade button
  upgradeButton_ = sf::RectangleShape(sf::Vector2f(100, 50));
  upgradeButton_.setFillColor(sf::Color::Red);
  upgradeButton_.setPosition(sf::Vector2f(width_ - 150, 300));

  // Label for the upgrade button
  upgradeLabel_ = sf::Text("Upgrade", arial_, 20);
  upgradeLabel_.setFillColor(sf::Color::Black);
  upgradeLabel_.setPosition(width_ - 140, 315);

  // Info for the upgrade button
  upgradeInfo_ = sf::Text("", arial_, 20);
  upgradeInfo_.setFillColor(sf::Color::Black);
  upgradeInfo_.setPosition(width_ - 140, 370);
}

void GUI::pause(bool isPaused) {
  if (!isPaused) {
    paused_ = false;
    pauseButtonText_.setString("Pause");
  } else {
    paused_ = true;
    pauseButtonText_.setString("Play");
  }
}

bool GUI::checkTowerButtonBounds(sf::Vector2f pos) {
  if (tileSelectionMode_ == tower) {
    return false;
  } else if (towerBox1_.getGlobalBounds().contains(pos)) {
    selectedTower_ = pawn;
    return true;
  } else if (towerBox2_.getGlobalBounds().contains(pos)) {
    selectedTower_ = king;
    return true;
  } else if (towerBox3_.getGlobalBounds().contains(pos)) {
    selectedTower_ = rook;
    return true;
  } else if (towerBox4_.getGlobalBounds().contains(pos)) {
    selectedTower_ = queen;
    return true;
  } else {
    return false;
  }
}

bool GUI::upgradeTower(int* score) {
  if (tileSelectionMode_ == tower) {
    TowerTile* ttile = (TowerTile*)selectedTile_;
    auto info = ttile->GetTower()->GetNextUpgrade();
    if (ttile->GetTower()->Upgrade(*score, tiles_)) {
      *score = *score - std::get<0>(info);
      setScore(*score);
      updateTiles();
      highlight(ttile->GetTower()->GetAllTargetTiles(tiles_), sf::Color::Black);
      highlight({selectedTile_}, sf::Color::Red);
      return true;
    }
  }
  return false;
}

void GUI::createAmmunition(std::pair<int, int> from, Tile* to) {
  int x = 0;
  int y = 0;
  for (int row = 0; row < windowRows_; row++) {
    for (int column = 0; column < windowColumns_; column++) {
      if ((*tiles_)[row][column] == to) {
        y = row;
        x = column;
      }
    }
  }

  float xdiff = (float)(x - from.first) * TILESIZE / SHELLSTEPS;
  float ydiff = (float)(y - from.second) * TILESIZE / SHELLSTEPS;

  sf::RectangleShape shell(sf::Vector2f(10, 10));
  shell.setFillColor(sf::Color::Red);
  shell.setPosition((from.first + 0.5) * TILESIZE,
                    (from.second + 0.5) * TILESIZE);
  ammo_[std::make_pair(xdiff, ydiff)] = shell;
  shellcounter_ = 0;
}

bool GUI::moveAmmunition() {
  if (shellcounter_ == SHELLSTEPS) {
    ammo_.clear();
    return true;
  } else {
    for (auto shell : ammo_) {
      auto shot = shell.second;
      shot.move(shell.first.first, shell.first.second);
      ammo_[shell.first] = shot;
    }
    shellcounter_++;
    return false;
  }
}

void GUI::loadUpgradeInfo() {
  if (tileSelectionMode_ == tower) {
    TowerTile* ttile = (TowerTile*)selectedTile_;
    auto info = ttile->GetTower()->GetNextUpgrade();
    if (std::get<0>(info) < 0) {
      upgradeInfo_.setString("Maximum\nupgrade\nreached");
    } else {
      std::stringstream description;
      description << "Cost: " << std::get<0>(info) << "\n";
      switch (std::get<1>(info)) {
        case speed:
          description << "Speed +";
          break;

        case damage:
          description << "Damage +";
          break;

        case range:
          description << "Range +";

        default:
          break;
      }
      description << std::get<2>(info) << std::endl;
      upgradeInfo_.setString(description.str());
    }
  }
}

bool GUI::release(Tower** spot, int* score) {
  sf::Vector2f pos = getMousePos();
  sf::Vector2i gridpos;
  if (posAsGrid(pos, &gridpos)) {
    if (tileSelectionMode_ == empty) {
      Tower* newtower;
      TowerTile* newtile;
      int price;
      switch (selectedTower_) {
        case pawn:
          newtower = new Pawn(gridpos.x, gridpos.y, tiles_);
          price = Pawn::GetPrice();
          newtile = new TowerTile();
          break;

        case king:
          newtower = new King(gridpos.x, gridpos.y, tiles_);
          price = King::GetPrice();
          newtile = new TowerTile();
          break;

        case rook:
          newtower = new Rook(gridpos.x, gridpos.y, tiles_);
          price = Rook::GetPrice();
          newtile = new TowerTile();
          break;

        case queen:
          newtower = new Queen(gridpos.x, gridpos.y, tiles_);
          price = Queen::GetPrice();
          newtile = new TowerTile();
          break;

        default:
          return false;
      }

      // check whether we can afford to buy the tower
      if (price <= *score) {
        *score -= price;
        setScore(*score);
        newtile->SetTower(newtower);
        auto curr = (*tiles_)[gridpos.y][gridpos.x];
        delete (curr);
        (*tiles_)[gridpos.y][gridpos.x] = newtile;
        *spot = newtower;
        selectedTower_ = NoTower;
        return true;
      } else {
        delete (newtower);
        delete (newtile);
        selectedTower_ = NoTower;
        return false;
      }
    }
  }
  selectedTower_ = NoTower;
  return false;
}

void GUI::selectTile() {
  sf::Vector2f pos = getMousePos();
  sf::Vector2i gridpos;

  if (posAsGrid(pos, &gridpos)) {
    Tile* selection = (*tiles_)[gridpos.y][gridpos.x];
    if (selectedTile_ != selection) {
      selectedTile_ = selection;
      std::string type = selectedTile_->GetType();
      if (type == "tower" && selectedTower_ == NoTower) {
        tileSelectionMode_ = tower;
        loadUpgradeInfo();
      } else if (type == "empty" && selectedTower_ != NoTower) {
        tileSelectionMode_ = empty;
      } else {
        tileSelectionMode_ = none;
      }

      updateTiles();
      if (tileSelectionMode_ == tower) {
        TowerTile* tow = (TowerTile*)selectedTile_;
        highlight(tow->GetTower()->GetAllTargetTiles(tiles_), sf::Color::Black);
        highlight(gridpos, sf::Color::Red);
      } else if (tileSelectionMode_ == empty) {
        visualizeRange(gridpos);
        highlight(gridpos, sf::Color::Red);
      }
    }
  }
}

void GUI::highlight(sf::Vector2i gridpos, sf::Color color) {
  auto gtile = guitiles_[getTile(gridpos)];

  gtile.setSize(sf::Vector2f(TILESIZE - 10, TILESIZE - 10));
  gtile.move(5, 5);
  gtile.setOutlineThickness(3.f);
  gtile.setOutlineColor(color);

  highlightGuitiles_.push_back(gtile);
}

void GUI::highlight(std::vector<Tile*> tiles, sf::Color color) {
  for (auto tile : tiles) {
    auto gtile = guitiles_[tile];
    gtile.setSize(sf::Vector2f(TILESIZE - 10, TILESIZE - 10));
    gtile.move(5, 5);
    gtile.setOutlineThickness(3.f);
    gtile.setOutlineColor(color);
    highlightGuitiles_.push_back(gtile);
  }
}

void GUI::visualizeRange(sf::Vector2i gridpos) {
  std::vector<Tile*> targets;
  switch (selectedTower_) {
    case pawn:
      targets = Pawn::StaticGetAllTargetTiles(tiles_, gridpos.x, gridpos.y);
      break;
    case king:
      targets = King::StaticGetAllTargetTiles(tiles_, gridpos.x, gridpos.y);
      break;
    case rook:
      targets = Rook::StaticGetAllTargetTiles(tiles_, gridpos.x, gridpos.y);
      break;
    case queen:
      targets = Queen::StaticGetAllTargetTiles(tiles_, gridpos.x, gridpos.y);
      break;
    default:
      return;
  }
  highlight(targets, sf::Color::Black);
}
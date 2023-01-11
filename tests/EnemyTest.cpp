#include "EnemyTest.hpp"

int EnemyTest() {
  SmallEnemy* small1 = new SmallEnemy();
  SmallEnemy* small2 = new SmallEnemy();
  SmallEnemy* small3 = new SmallEnemy();
  SmallEnemy* small4 = new SmallEnemy();
  BigEnemy* big = new BigEnemy();
  SplitterEnemy* splitter = new SplitterEnemy();

  std::cout << "Enemies:" << std::endl;
  std::cout << " -" << *small1 << std::endl;
  std::cout << " -" << *big << std::endl;
  std::cout << " -" << *splitter << std::endl << std::endl;

  big->GetHit(2);
  std::cout << (big->GetHealth() == 1 ? "GetHit() working"
                                      : "GetHit() not working")
            << std::endl
            << std::endl;

  EmptyTile* emptyTile = new EmptyTile();
  TowerTile* towerTile = new TowerTile();
  PathTile* path3 = new PathTile(3);
  PathTile* path2 = new PathTile(2, path3);
  PathTile* path1 = new PathTile(1, path2);

  path1->SetEnemy(small1);

  std::cout << "Tiles:" << std::endl;
  std::cout << " -" << *emptyTile << std::endl;
  std::cout << " -" << *towerTile << std::endl;
  std::cout << " -" << *path1 << std::endl;
  std::cout << " -" << *path2 << std::endl;
  std::cout << " -" << *path3 << std::endl << std::endl;

  std::cout << "nextPathTile of path #1 is " << *path1->GetNextPathTile()
            << std::endl
            << std::endl;

  // enemy should die and return the reward
  std::cout << *path1 << std::endl;
  size_t reward = path1->AttackEnemy(3);
  std::cout << "Reward: " << reward << std::endl;
  std::cout << *path1 << std::endl;

  std::cout << "Testing movement:" << std::endl;

  // create map and waves from file
  std::vector<std::vector<Tile*>> map;
  std::vector<std::vector<Enemy*>> waves;
std:
  tie(map, waves) = GenerateMapAndWaves("../src/maps/test_map.txt");
  PathTile* firstPathTile = GetFirstPathTile(&map);

  // move enemies and add enemy to map
  MoveEnemiesAndCheckGameover(firstPathTile, small2);

  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies

  // move enemies and add enemy to map
  MoveEnemiesAndCheckGameover(firstPathTile, small3);

  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies

  // move enemies and add enemy to map
  MoveEnemiesAndCheckGameover(firstPathTile, small4);
  // Enemies can be added to map with zero tile gap

  // move enemies and add enemy to map
  MoveEnemiesAndCheckGameover(firstPathTile, big);

  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies
  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies
  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies
  MoveEnemiesAndCheckGameover(firstPathTile);  // move enemies
  bool isGameover = MoveEnemiesAndCheckGameover(firstPathTile);
  std::cout << (isGameover ? "Gameover working" : "Gameover not working")
            << std::endl
            << std::endl;

  delete splitter;

  delete emptyTile;
  delete towerTile;
  delete path1;
  delete path2;
  delete path3;

  // delete all Tiles from map
  for (vector<Tile*> row : map) {
    for (Tile* tile : row) {
      delete tile;  // enemies inside PathTile will be deleted also
    }
  }

  return 0;
}
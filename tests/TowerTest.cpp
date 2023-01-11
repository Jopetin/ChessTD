#include "TowerTest.hpp"

int TowerTest() {
  std::vector<std::vector<Tile *>> map;
  std::vector<std::vector<Enemy *>> waves;
std:
  tie(map, waves) = GenerateMapAndWaves("../src/maps/test_map.txt");

  std::vector<std::vector<Tile *>> *ref = &map;
  Rook *aRook = new Rook(0, 2, ref);
  auto tiles = Rook::StaticGetAllTargetTiles(ref, 0, 2);
  Rook *bRook = new Rook(2, 1, ref);
  BigEnemy *bigEnemyFirst = new BigEnemy();
  BigEnemy *bigEnemySecond = new BigEnemy();
  BigEnemy *bigEnemyThird = new BigEnemy();
  auto first = GetFirstPathTile(ref);
  first->SetEnemy(bigEnemyFirst);
  auto third = first->GetNextPathTile()->GetNextPathTile();
  third->SetEnemy(bigEnemySecond);
  auto sixth = third->GetNextPathTile()->GetNextPathTile()->GetNextPathTile();
  sixth->SetEnemy(bigEnemyThird);
  std::tuple<int, upgradeType, int> upgrade = aRook->GetNextUpgrade();
  std::cout << "----------------\nTesting upgrade system and "
               "basic tower variables\n----------------"
            << std::endl;
  std::cout << "Price of a Rook: " << Rook::GetPrice() << "\n"
            << *aRook << "\nNext upgrade:\n"
            << "Price: " << std::get<0>(upgrade)
            << "\nType: (speed, damage, range)" << std::get<1>(upgrade)
            << "\nUpgrade amount: " << std::get<2>(upgrade) << std::endl;
  for (int i : {40, 50, 75, 200, 400, 400}) {
    bool success = bRook->Upgrade(i, ref);
    if (success) {
      std::cout << "upgrade succeeded with money: " << i << "\nTower now:\n"
                << *bRook << "And next upgrade costs: "
                << std::get<0>(bRook->GetNextUpgrade()) << "\n"
                << std::endl;
    } else {
      std::cout << "failed with money: " << i << ", tower now\n"
                << *bRook << std::endl;
    }
    if (std::get<0>(bRook->GetNextUpgrade()) == -1) {
      std::cout << "Maximum level reached!\n" << std::endl;
    }
  }
  std::cout << "----------------\nTesting towers shooting "
               "and retrieving rewards\n----------------"
            << std::endl;
  std::cout << "Enemies at beginning\n"
            << *(first->GetEnemy()) << " Path tile 0\n"
            << *(third->GetEnemy()) << " Path tile 2\n"
            << *(sixth->GetEnemy()) << " Path tile 5\n"
            << std::endl;
  auto values = aRook->Shoot();
  if (values.first > 0 && values.second == static_cast<Tile *>(third)) {
    std::cout << "Tower shot and killed the enemy, remaining enemies are:"
              << *(first->GetEnemy()) << *(sixth->GetEnemy())
              << "\nAnd the reward was:" << values.first << std::endl;
  }
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  std::cout << "No enemy should not take damage, on cooldown\n"
            << *(first->GetEnemy()) << *(sixth->GetEnemy()) << std::endl;
  values = aRook->Shoot();
  if (values.first > 0 && values.second == static_cast<Tile *>(first)) {
    std::cout << "Tower shot and killed the enemy. last one remaining is:"
              << *(sixth->GetEnemy()) << "\nAnd the reward was:" << values.first
              << std::endl;
  }
  std::cout << "Upgrading Rook to reach the last enemy\n" << std::endl;
  aRook->Upgrade(50, ref);
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  aRook->Shoot();
  std::cout << "Should not have taken damage, cooldown \n"
            << *(sixth->GetEnemy()) << std::endl;
  values = aRook->Shoot();
  if (values.first > 0 && values.second == static_cast<Tile *>(sixth)) {
    std::cout << "Tower shot and killed the last enemy\nAnd the reward was:"
              << values.first << std::endl;
  }
  delete (aRook);
  delete (bRook);
  SmallEnemy *smallEnemyFirst = new SmallEnemy();
  SmallEnemy *smallEnemySecond = new SmallEnemy();
  SmallEnemy *smallEnemyThird = new SmallEnemy();
  std::cout << "\nAll enemies dead, adding new ones and testing other towers"
            << std::endl;
  first->SetEnemy(smallEnemyFirst);
  third->SetEnemy(smallEnemySecond);
  sixth->SetEnemy(smallEnemyThird);
  std::cout << "Enemies currently\n"
            << *(first->GetEnemy()) << " Path tile 0\n"
            << *(third->GetEnemy()) << " Path tile 2\n"
            << *(sixth->GetEnemy()) << " Path tile 5\n"
            << std::endl;
  Queen *queen = new Queen(2, 3, ref);
  std::cout << "\nAdded new tower:\n"
            << *queen << "\nShould reach and kill enemy in path tile 5"
            << std::endl;
  values = queen->Shoot();
  if (values.first > 0 && values.second == static_cast<Tile *>(sixth)) {
    std::cout << "Tower shot and killed the enemy, remaining enemies are:"
              << *(first->GetEnemy()) << *(third->GetEnemy())
              << "\nAnd the reward was:" << values.first << std::endl;
  } else {
    std::cout << "Tower didn't kill anything, remaining enemies are:"
              << *(first->GetEnemy()) << *(third->GetEnemy())
              << *(sixth->GetEnemy()) << std::endl;
  }
  delete (queen);
  King *king = new King(0, 2, ref);
  std::cout << "\nAdded new tower:\n"
            << *king << "\nShould reach and kill enemy in path tile 2"
            << std::endl;
  values = king->Shoot();
  if (values.first == 10 && values.second == static_cast<Tile *>(third)) {
    std::cout << "Tower shot and killed the enemy, remaining enemy is:"
              << *(first->GetEnemy())
              << "\nAnd the reward was double of what queen got:"
              << values.first << std::endl;
  }

  delete (king);
  Pawn *pawn = new Pawn(1, 0, ref);
  std::cout << "\nAdded new tower:\n"
            << *pawn << "\nShould reach and kill enemy in path tile 0"
            << std::endl;
  values = pawn->Shoot();
  if (values.first > 0 && values.second == static_cast<Tile *>(first)) {
    std::cout << "Tower shot and killed the last enemy.\nAnd the reward was:"
              << values.first << std::endl;
  }
  std::cout << "----------------\nTower testing "
               "done!\n----------------"
            << std::endl;
  delete (pawn);
  for (vector<Tile *> row : map) {
    for (Tile *tile : row) {
      delete tile;  // enemies inside PathTile will be deleted also
    }
  }
  return 1;
}
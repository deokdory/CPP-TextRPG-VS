#include "pch.h"
#include "Combat.h"

//장소 별 적 인원 및 확률

#define FOREST_ENEMIES_MIN 1
#define FOREST_ENEMIES_MAX 2
#define FOREST_ENEMIES_LVL_MIN 1
#define FOREST_ENEMIES_LVL_MAX 2
#define FOREST_ENEMY_ADD_PERCENTAGE 0.5

#define CAVE_ENEMIES_MIN 1
#define CAVE_ENEMIES_MAX 3
#define CAVE_ENEMIES_LVL_MIN 2
#define CAVE_ENEMIES_LVL_MAX 3
#define CAVE_ENEMY_ADD_PERCENTAGE 0.5

#define MOUNTAIN_ENEMIES_MIN 1
#define MOUNTAIN_ENEMIES_MAX 3
#define MOUNTAIN_ENEMIES_LVL_MIN 4
#define MOUNTAIN_ENEMIES_LVL_MAX 4
#define MOUNTAIN_ENEMY_ADD_PERCENTAGE 0.75

void Combat(Hero** Player, Place _place) {
  int allies_alive = 0;
  //PlayerArrayAlign(Player);
  int num_of_playble_heroes = GetNumOfPlayableHeroes(Player);
  for (int i = 0; i < num_of_playble_heroes; i++) {
    if (!(Player[i]->CheckIsDead())) {
      allies_alive++;
    }
  }
  int enemies_alive = GetEnemiesPersonnel(_place);
  Enemy* enemy = new Enemy[enemies_alive];
  int total_reward_gold = 0;
  for (int i = 0; i < enemies_alive; i++) {
    Enemy enemy_temp(GetEnemyName(_place), GetEnemyLvl(_place));
    if (&enemy[i] != nullptr) {
      enemy[i] = enemy_temp;
      total_reward_gold += enemy[i].GetRewardGold();
      enemy[i].PrintStatus(60);
    } else {
      std::cout << "ERROR:enemy[" << i << "] is nullptr!" << std::endl;
    }
  }
  Character* SpdComparison[PARTY_MAX * 2];

  while (true) {
    if (!allies_alive || !enemies_alive) {  // 전투 종료 조건
      break;
    }

    system("cls");

    gotoy(0);
    for (int i = 0; i < num_of_playble_heroes; i++) {
      if (!(Player[i]->CheckIsDead())) {
        Player[i]->PrintStatus();
      }
    }
    gotoy(0);
    for (int i = 0; i < enemies_alive; i++) {
      if (!(enemy[i].CheckIsDead())) {
        enemy[i].PrintStatus(60);
      }
    }
    gotoxy(0, 24);
    {
      int index;
      for (int i = 0; i < allies_alive; i++) {
        SpdComparison[index] = Player[i];
        index++;
      }
      for (int i = 0; i < enemies_alive; i++) {
        SpdComparison[index] = &enemy[i];
        index++;
      }
    system("pause");
  }
  if (allies_alive && !enemies_alive) {  // 승리
    // gold += total_reward_gold;
    std::cout << total_reward_gold << "G 를 획득했습니다" << std::endl;
    SYSTEM_MESSAGE_DELAY;
  } else if (!allies_alive && enemies_alive) {  //패배
    std::cout << "당신은 패배했습니다..." << std::endl;
    SYSTEM_MESSAGE_DELAY;
  } else {  // 도망
    std::cout << "당신은 도망쳤습니다." << std::endl;
    SYSTEM_MESSAGE_DELAY;
  }

  delete[] enemy;
}

int GetEnemiesPersonnel(Place _place) {
  int enemies_min = 1;
  int enemies_max = 1;
  double percent = 1;

  switch (_place) {
    case Place::FOREST: {
      enemies_min = FOREST_ENEMIES_MIN;
      enemies_max = FOREST_ENEMIES_MAX;
      break;
    }
    case Place::CAVE: {
      enemies_min = CAVE_ENEMIES_MIN;
      enemies_max = CAVE_ENEMIES_MAX;
      break;
    }
    case Place::MOUNTAIN: {
      enemies_min = MOUNTAIN_ENEMIES_MIN;
      enemies_max = MOUNTAIN_ENEMIES_MAX;
      break;
    }
  }
  int enemies_personnel = enemies_min;
  double random = 0;

  if (enemies_min > enemies_max) {
    std::cout << "ERROR : enemies_min is higher than enemies_max ! so swapped"
              << std::endl;
    std::swap(enemies_min, enemies_max);
  }

  for (int i = 0; i < enemies_max - enemies_min; i++) {
    random = random();
    if (enemies_personnel >= enemies_max) {
      enemies_personnel = enemies_max;
      break;
    }
    if (random < percent) {
      enemies_personnel++;
    } else {
      continue;
    }
  }
  return enemies_personnel;
}

int GetEnemyLvl(Place _place) {
  int lvl_min = 1;
  int lvl_max = 1;
  int lvl = 1;
  switch (_place) {
    case Place::FOREST: {
      lvl_min = FOREST_ENEMIES_LVL_MIN;
      lvl_max = FOREST_ENEMIES_LVL_MAX;
      break;
    }
    case Place::CAVE: {
      lvl_min = CAVE_ENEMIES_LVL_MIN;
      lvl_max = CAVE_ENEMIES_LVL_MAX;
      break;
    }
    case Place::MOUNTAIN: {
      lvl_min = MOUNTAIN_ENEMIES_LVL_MIN;
      lvl_max = MOUNTAIN_ENEMIES_LVL_MAX;
      break;
    }
  }
  double random = random();
  double ratio = 1.0;
  if (lvl_min > lvl_max) {
    std::cout << "ERROR : lvl_min is higher than lvl_max ! so swapped"
              << std::endl;
    std::swap(lvl_min, lvl_max);
  }
  int lvl_range = lvl_max - lvl_min + 1;

  ratio /= lvl_range;

  for (int i = 0; i < lvl_range; i++) {
    if (random < ratio * (i + 1)) {
      lvl = lvl_min + i;
      break;
    } else {
      continue;
    }
  }
  return lvl;
}

std::string GetEnemyName(Place _place) {
  std::string name = "NONE";
  switch (_place) {
    case Place::FOREST: {
      name = "WOLF";
      break;
    }
    case Place::CAVE: {
      name = "GOBLIN";
      break;
    }
    case Place::MOUNTAIN: {
      name = "DEVILKING";
      break;
    }
  }
  return name;
}
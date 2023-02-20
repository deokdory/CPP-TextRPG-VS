#include "pch.h"
#include "Combat.h"

Combat::Combat(Place _place) {
  SetEnemy(_place);
  while (true)
    
    if (!allies_alive || !enemies_alive) { // 전투 종료 조건
      break;
    }
}

Combat::~Combat() {
  if (allies_alive && !enemies_alive) {  // 승리
    gold += total_reward_gold;
    std::cout << total_reward_gold << "G 를 획득했습니다" << std::endl;
  } else if (!allies_alive && enemies_alive) {  //패배
    std::cout << "당신은 패배했습니다..." << std::endl;
  } else {  // 도망
    std::cout << "당신은 도망쳤습니다." << std::endl;
  }
}

void Combat::SetEnemy(Place _place) {
  switch (_place) {
    case Place::FOREST: {
      enemy = new Enemy("WOLF", 1);
      break;
    }
    case Place::CAVE: {
      enemy = new Enemy("GOBLIN", 3);
      break;
    }
    case Place::MOUNTAIN: {
      enemy = new Enemy("DEVILKING", 5);
      break;
    }
  }
}
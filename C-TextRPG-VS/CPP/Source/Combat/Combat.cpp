#include "pch.h"
#include "Combat.h"

Combat::Combat(Place _place) {
  SetEnemy(_place);
  while (true)
    
    if (!allies_alive || !enemies_alive) { // ���� ���� ����
      break;
    }
}

Combat::~Combat() {
  if (allies_alive && !enemies_alive) {  // �¸�
    gold += total_reward_gold;
    std::cout << total_reward_gold << "G �� ȹ���߽��ϴ�" << std::endl;
  } else if (!allies_alive && enemies_alive) {  //�й�
    std::cout << "����� �й��߽��ϴ�..." << std::endl;
  } else {  // ����
    std::cout << "����� �����ƽ��ϴ�." << std::endl;
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
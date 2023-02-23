#include "pch.h"
#include "main.h"


int main() {
  Initialize();
  
  Hero* Player[PARTY_MAX] = {};
  GameManager Game;

  NewPlayerCharacter(Player, 2);
  NewPlayerCharacter(Player, 1);

  Player[0]->GiveSkill(STRONG_ATTACK);

  Combat(Game, Player, Place::FOREST);
}

  


  //gotoxy(60, 0);
  //std::cout << "숲 몬스터 테스트" << std::endl;
  //Combat(Place::FOREST);
  //ENDL;
  //
  //std::cout << "동굴 몬스터 테스트 " << std::endl;
  //Combat(Place::CAVE);
  //ENDL;
  //
  //std::cout << "산 몬스터 테스트" << std::endl;
  //Combat(Place::MOUNTAIN);
  //ENDL;
 //

void Initialize() {
  srand((unsigned)time(NULL));  // 난수 seed 생성
}




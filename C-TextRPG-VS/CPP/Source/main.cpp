#include "pch.h"
#include "main.h"


int main() {
  Initialize();
  
  Hero* Player[PARTY_MAX] = {};
  GameManager Game;

  NewPlayerCharacter(Player, 1);
  NewPlayerCharacter(Player, 1);
  //NewPlayerCharacter(Player, 3);

  Player[0]->GiveSkill(STRONG_ATTACK);
  
  Combat(Game, Player, Place::FOREST);
}

  //gotoxy(60, 0);
  //std::cout << "�� ���� �׽�Ʈ" << std::endl;
  //Combat(Place::FOREST);
  //ENDL;
  //
  //std::cout << "���� ���� �׽�Ʈ " << std::endl;
  //Combat(Place::CAVE);
  //ENDL;
  //
  //std::cout << "�� ���� �׽�Ʈ" << std::endl;
  //Combat(Place::MOUNTAIN);
  //ENDL;
 //

void Initialize() {
  srand((unsigned)time(NULL));  // ���� seed ����
}
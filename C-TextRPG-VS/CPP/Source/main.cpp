#include "pch.h"
#include "main.h"


int main() {
  Hero* Player[PARTY_MAX] = {};

  NewPlayerCharacter(Player);
  NewPlayerCharacter(Player);

  Combat(Player, Place::FOREST);
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




#include "pch.h"
#include "main.h"

int main() {
  std::string name;
  while (true) {
    system("cls");

    std::string temp;
    std::cout << "이름? : ";
    std::cin >> temp;

    if (temp.length() > NAME_LIMIT) {
      std::cout << "이름 길이 제한은 영어" << NAME_LIMIT << "자, 한글 "
                << NAME_LIMIT / 2 << "자 입니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    } else {
      name = temp;
      break;
    }
  }
  Hero Player(name, 1);
  Player.PrintStatus();

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

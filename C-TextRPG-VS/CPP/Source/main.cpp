#include "pch.h"
#include "main.h"
 
int main() {
  Initialize();

  gotoxy(60, 0);
  std::cout << "�� ���� �׽�Ʈ" << std::endl;
  Combat(Place::FOREST);
  ENDL;

  std::cout << "���� ���� �׽�Ʈ " << std::endl;
  Combat(Place::CAVE);
  ENDL;

  std::cout << "�� ���� �׽�Ʈ" << std::endl;
  Combat(Place::MOUNTAIN);
  ENDL;

}

void Initialize() {
  srand((unsigned)time(NULL));  // ���� seed ����

  std::string name;
  while (true) {
    system("cls");

    std::string temp;
    std::cout << "�̸�? : ";
    std::cin >> temp;

    if (temp.length() > NAME_LIMIT) {
      std::cout << "�̸� ���� ������ ����" << NAME_LIMIT << "��, �ѱ� "
                << NAME_LIMIT / 2 << "�� �Դϴ�." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    } else {
      name = temp;
      break;
    }
  }
  Hero Player(name, 1);
  Player.PrintStatus();
}


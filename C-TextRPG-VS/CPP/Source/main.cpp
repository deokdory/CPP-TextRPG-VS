#include "pch.h"
#include "main.h"
 
int main() {
  Enemy* enemy = new Enemy("WOLF", 1);
  std::cout << enemy->GetRewardGold() << std::endl;
  std::cout << enemy->GetRewardExp() << std::endl;
  delete enemy;
}

//	do
//	{
//		system("cls");
//		
//		if (temp.length > NAME_LIMIT) {
//
//		}
//
//		std::string temp;
//		std::cout << "이름? : ";
//		std::cin >> temp;
//	} while(temp.length > NAME_LIMIT)
//	Hero(temp, 1); // 영웅 생성
//
//  return 0;
//}

void Initialize() {
}
#include "pch.h"
#include "master.h"
 
int main() {
	
	do
	{
		system("cls");
		
		if (temp.length > NAME_LIMIT) {

		}

		std::string temp;
		std::cout << "이름? : ";
		std::cin >> temp;
	} while(temp.length > NAME_LIMIT)
	Hero(temp, 1); // 영웅 생성

  return 0;
}

void Initialize() {

}
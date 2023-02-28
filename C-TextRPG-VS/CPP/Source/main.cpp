#include "main.h"
#include "pch.h"

enum ActionInLobby {
  LOBBY_INVENTORY = 1,
  LOBBY_VISIT_SHOP,
  LOBBY_SKILL,
  LOBBY_QUEST_STATUS,

  LOBBY_GO_COMBAT = 0
};

int main() {
  Initialize();

  Hero* Player[PARTY_MAX] = {};
  GameManager Game;

  NewPlayerCharacter(Player, 1);
  NewPlayerCharacter(Player, 1);
  NewPlayerCharacter(Player, 1);

  Player[0]->GiveSkill(STRONG_ATTACK);

  QuestList::NewQuestList(1);  // 늑대 사냥 퀘스트 부여

  Inventory::GotItem(1, 3);  // 포션 지급

  while (true) {
    Clear;

    LobbyPlayerStatus(Player);

    std::cout << "보유 골드 : " << Game.GetGold() << "G"
              << "\t\t진행중인 퀘스트 : " << QuestList::GetLength() << "개";

    ClearFromY(9, 20);

    switch (Lobby()) {
      case LOBBY_INVENTORY:
        Inventory::Open(Player);
        break;
      case LOBBY_VISIT_SHOP: {
        Shop();
        break;  // 상점 방문
      }
      case LOBBY_SKILL: {
        Character* who = SelectTarget(Player);

        if (who == nullptr) break;

        Hero* hero = dynamic_cast<Hero*>(who);
        ClearFromY(9, 20);
        hero->PrintSkillsAll();
        Pause;
        break;
      }
      case LOBBY_QUEST_STATUS: {
        ClearFromY(9, 20);
        QuestList::Open();
        break;
      }
      case LOBBY_GO_COMBAT: {
        std::cout << "목적지를 선택하세요." << std::endl;
        std::cout << "1. 숲 ( 권장 평균 레벨 : 1)\n2. 동굴 (권장 평균 레벨 : "
                     "3)\n3.산 (권장 평균 레벨 : 5)\n0. 취소\n";
        std::cout << "입력 : ";
        int destination = 0;
        std::cin >> destination;

        switch (destination) {
          case 0:
            break;
          case 1:
            Combat(Game, Player, Place::FOREST);
            break;
          case 2:
            Combat(Game, Player, Place::CAVE);
            break;
          case 3:
            Combat(Game, Player, Place::MOUNTAIN);
            break;
          default:
            std::cout << "잘못된 입력입니다." << std::endl;
            SYSTEM_MESSAGE_DELAY;
            break;
        }
        break;
      }
      default:
        std::cout << "잘못된 입력입니다." << std::endl;
        SYSTEM_MESSAGE_DELAY;
        break;
    }
  }
}

// gotoxy(60, 0);
// std::cout << "숲 몬스터 테스트" << std::endl;
// Combat(Place::FOREST);
// ENDL;
//
// std::cout << "동굴 몬스터 테스트 " << std::endl;
// Combat(Place::CAVE);
// ENDL;
//
// std::cout << "산 몬스터 테스트" << std::endl;
// Combat(Place::MOUNTAIN);
// ENDL;
//

void Initialize() {
  srand((unsigned)time(NULL));  // 난수 seed 생성
}

int Lobby() {
  std::cout << "원하는 행동을 선택하세요." << std::endl;
  std::cout << "1. 인벤토리 열기   2. 포션상점 방문   3. 캐릭터 스킬 보유 현황   "
               "4. 퀘스트 현황   0. 전투"
            << std::endl;
  std::cout << "입력 : ";
  int action = 0;
  std::cin >> action;

  ENDL;

  if (0 <= action && action <= 4)
    return action;
  else {
    return -1;
  }
  SYSTEM_MESSAGE_DELAY;
}
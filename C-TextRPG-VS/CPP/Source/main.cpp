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

  QuestList::NewQuestList(1);  // ���� ��� ����Ʈ �ο�

  Inventory::GotItem(1, 3);  // ���� ����

  while (true) {
    Clear;

    LobbyPlayerStatus(Player);

    std::cout << "���� ��� : " << Game.GetGold() << "G"
              << "\t\t�������� ����Ʈ : " << QuestList::GetLength() << "��";

    ClearFromY(9, 20);

    switch (Lobby()) {
      case LOBBY_INVENTORY:
        Inventory::Open(Player);
        break;
      case LOBBY_VISIT_SHOP: {
        Shop();
        break;  // ���� �湮
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
        std::cout << "�������� �����ϼ���." << std::endl;
        std::cout << "1. �� ( ���� ��� ���� : 1)\n2. ���� (���� ��� ���� : "
                     "3)\n3.�� (���� ��� ���� : 5)\n0. ���\n";
        std::cout << "�Է� : ";
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
            std::cout << "�߸��� �Է��Դϴ�." << std::endl;
            SYSTEM_MESSAGE_DELAY;
            break;
        }
        break;
      }
      default:
        std::cout << "�߸��� �Է��Դϴ�." << std::endl;
        SYSTEM_MESSAGE_DELAY;
        break;
    }
  }
}

// gotoxy(60, 0);
// std::cout << "�� ���� �׽�Ʈ" << std::endl;
// Combat(Place::FOREST);
// ENDL;
//
// std::cout << "���� ���� �׽�Ʈ " << std::endl;
// Combat(Place::CAVE);
// ENDL;
//
// std::cout << "�� ���� �׽�Ʈ" << std::endl;
// Combat(Place::MOUNTAIN);
// ENDL;
//

void Initialize() {
  srand((unsigned)time(NULL));  // ���� seed ����
}

int Lobby() {
  std::cout << "���ϴ� �ൿ�� �����ϼ���." << std::endl;
  std::cout << "1. �κ��丮 ����   2. ���ǻ��� �湮   3. ĳ���� ��ų ���� ��Ȳ   "
               "4. ����Ʈ ��Ȳ   0. ����"
            << std::endl;
  std::cout << "�Է� : ";
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
#include "Quest.h"

#include "pch.h"

Quest::Quest(int index, std::string name, std::string description,
             QuestType type, int reward_exp, int reward_gold, Item* reward_item)
    : index(0),
      name(name),
      description(description),
      type(type),
      reward_exp(reward_exp),
      reward_gold(reward_gold),
      reward_item(reward_item) {}

void Quest::QuestComplete(Hero** player) {
  std::cout << GetName() << " 퀘스트를 완료하셨습니다." << std::endl;

  for (int i = 0; i < PARTY_MAX; i++) {
    if (player[i] != nullptr) {
      player[i]->GiveExp(reward_exp);
    }
  }
  GameManager::AddGold(reward_gold);
  CompletedQuest::NewCompletedQuest(index);
}

// 사냥 퀘스트
HuntQuest::HuntQuest(int _index, std::string _name, std::string _description,
                     QuestType _type, int _reward_exp, int _reward_gold,
                     int _target_enemy_index, int _target_enemy_goal,
                     int _count, Item* _reward_item)
    : Quest(_index, _name, _description, _type, _reward_exp, _reward_gold,
            _reward_item),
      target_enemy_index(_target_enemy_index),
      target_enemy_goal(_target_enemy_goal),
      count(_count) {}

bool HuntQuest::IsGoalAchieved() {
  bool is_goal_achieved = false;
  if (count >= target_enemy_goal) is_goal_achieved = true;
  return is_goal_achieved;
}

void HuntQuest::SetTargetEnemyIndex(int _target_index) {
  target_enemy_index = _target_index;
}

void HuntQuest::SetObjectiveCount(int _objective_count) {
  target_enemy_goal = _objective_count;
}

void HuntQuest::AddCount() { count++; }

void HuntQuest::PrintProgress() {
  double progress_percent = (double)count / target_enemy_goal * 100;
  std::cout << Enemy::GetNameWithIndex(target_enemy_index) << "사냥 : " << count
            << " / " << target_enemy_goal << " (" << progress_percent << "%)"
            << std::endl;
}

// 아이템 전달 퀘스트
SupplyQuest::SupplyQuest(int _index, std::string _name,
                         std::string _description, QuestType _type,
                         int _reward_exp, int _reward_gold,
                         int _required_item_index, int _required_item_count,
                         Item* _reward_item)
    : Quest(_index, _name, _description, _type, _reward_exp, _reward_gold,
            _reward_item),
      required_item_index(_required_item_index),
      required_item_count(_required_item_count) {}

int SupplyQuest::GetCount() const {
  Inventory* finder = Inventory::FindItem(required_item_index);
  if (finder != nullptr) {
    return finder->GetItemCount();
  } else {
    return 0;
  }
}

void SupplyQuest::SetRequiredItemIndex(int _index) {
  required_item_index = _index;
}

void SupplyQuest::SetRequiredItemCount(int _required_count) {
  required_item_count = _required_count;
}

void SupplyQuest::PrintProgress() {
  int count = GetCount();
  double progress_percent = (double)count / required_item_count * 100;
  std::cout << Enemy::GetNameWithIndex(required_item_index)
            << "전달 : " << count << " / " << required_item_count << " ("
            << progress_percent << "%)" << std::endl;
}
void SupplyQuest::AddCount() {}
bool SupplyQuest::IsGoalAchieved() {
  bool is_goal_achieved = false;
  if (GetCount() >= required_item_count) is_goal_achieved = true;
  return is_goal_achieved;
}

void SupplyQuest::QuestComplete(Hero** player) {
  Inventory* required_item = Inventory::FindItem(required_item_index);
  if (required_item != nullptr) {
    if (required_item->GetItemCount() >= required_item_count) {
      required_item->DecreaseItemCount(required_item_count);
      Quest::QuestComplete(player);
    }
  } else {
    std::cout << "ERROR:Quest goal is unfinished" << std::endl;
  }
}
/*
  QuestList* QuestList::Head = nullptr;
  QuestList* QuestList::Tail = nullptr;
  int QuestList::Length = 0;

  QuestList* QuestList::NewQuestList(){QuestList* quest_list = new Quest}

  QuestList*
  QuestList::NewQuestList(int _index) {
    QuestList* new_quest = nullptr;

    if (1 <= _index && _index <= 1000) {
    }
  }

  void QuestList::Push() {}

  void QuestList::Remove() {}

  void QuestList::RemoveAll() {}

  void QuestList::Open() {}

  const int QuestList::GetHighestLvlOfPlayer(Hero**) {}

  void QuestList::GiveUpQuest() {}
  */

Quest* NewQuest(int _index) {
  if (CompletedQuest::CheckIsCompletedQuest(_index)) {
    return nullptr;
  }

  if (1 <= _index && _index <= 1000) return NewHuntQuest(_index);
  // else if (1001 <= _index && _index <= 2000)
  //  return NewSupplyQuest(_index);
  else {
    std::cout << "Undefined Quest Index" << std::endl;
    system("pause");
    return nullptr;
  }
}

Quest* NewHuntQuest(int _index) {
  int index = _index;
  std::string name = "NULL";
  std::string description = "NULL";
  QuestType type = QuestType::HUNT;
  int target_enemy_index = 0;
  int target_enemy_goal = 0;
  int reward_exp = 0;
  int reward_gold = 0;
  Item* reward_item = nullptr;
  switch (_index) {
    type = QuestType::HUNT;
    case 1: {
      name = "늑대 잡기";
      description = "늑대 무서워 3마리 잡아줘";
      target_enemy_index = WOLF;
      target_enemy_goal = 3;
      reward_exp = 30;
      reward_gold = 100;
      break;
    }
    case 2: {
      name = "고블린 잡기";
      description = "고블린 무서워 3마리 잡아줘";
      target_enemy_index = GOBLIN;
      target_enemy_goal = 3;
      reward_exp = 60;
      reward_gold = 150;
      break;
    }
    case 3: {
      name = "마왕 잡기";
      description = "마왕 무서워 잡아줘";
      target_enemy_index = DEVILKING;
      target_enemy_goal = 1;
      reward_exp = 100;
      reward_gold = 1000;
      break;
    }
    default: {
      std::cout << "ERROR:Undefined Quest Index" << std::endl;
      system("pause");
      return nullptr;
    }
  }
  return new HuntQuest(index, name, description, type, reward_exp, reward_gold,
                       target_enemy_index, target_enemy_goal, 0, reward_item);
}

/*
Quest* NewSupplyQuest(int _index) {
  int index = _index;
  std::string name = "NULL";
  std::string description = "NULL";
  QuestType type = QuestType::HUNT;
  int required_item_index = 0;
  int required_item_count = 0;
  int reward_exp = 0;
  int reward_gold = 0;
  Item* reward_item = nullptr;
  switch (_index) {
    case 1001: {
      name = "늑대 이빨 갖고 싶어";
      description = "늑대 이빨이 필요해 3개 갖다줘";
      required_item_index = WOLF_TOOTH;
      required_item_count = 3;
      reward_exp = 45;
      reward_gold = 125;
      break;
    }
    default: {
      std::cout << "ERROR:Undefined Quest Index" << std::endl;
      system("pause");
      return nullptr;
    }
  }
  return new SupplyQuest(index, name, description, type, reward_exp,
                         reward_gold, required_item_index, required_item_count,
                         reward_item);
}
*/

QuestList* QuestList::Head = nullptr;
QuestList* QuestList::Tail = nullptr;
int QuestList::Length = 0;

QuestList::QuestList(int _index)
    : quest_in_progress(NewQuest(_index)), Next(nullptr), Prev(nullptr) {}

void QuestList::QuestCompleteChecker(Hero** Player) {
  if (!Head) return;

  QuestList* checker = Head;

  while (true) {
    if (checker->GetQuestInProgress()->IsGoalAchieved()) {
      checker->GetQuestInProgress()->QuestComplete(Player);
      checker->Remove();
    }

    if (checker->Next)
      checker = checker->Next;
    else
      break;
  }
}

void QuestList::NewQuestList(int _index) {
  QuestList* node = new QuestList(_index);

  if (node->GetQuestInProgress() != nullptr) {
    std::cout << node->GetQuestInProgress()->GetName()
              << " 퀘스트를 받았습니다." << std::endl;
    SYSTEM_MESSAGE_DELAY;
    node->Push();
  } else {
    delete node;
  }
}

void QuestList::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  }

  else {
    Tail->Next = this;
    Tail = this;
  }

  Length++;
}

void QuestList::Remove() {
  if (Head == this) {
    if (this->Next != nullptr) {
      Head = this->Next;
      delete this;
    } else {
      Head = Tail = nullptr;
      delete this;
    }
  }

  QuestList* cur = Head;

  while (true) {
    if (cur != nullptr) {
      if (this->Next != nullptr) {
        cur->Next = this->Next;
      } else {
        cur->Next = nullptr;
      }
      delete this;
    } else {
      cur = cur->Next;
    }
  }
  Length--;
}

void QuestList::RemoveAll() {
  if (Head == nullptr) {
    std::cout << "QuestList is null" << std::endl;
    system("pause");
    return;
  }

  if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  delete Head;
  Length = 0;
}

void QuestList::HuntQuestProgressChecker(int _index) {
  if (Head == nullptr) return;

  QuestList* checker = Head;
  Quest* quest_checker = checker->GetQuestInProgress();

  while (true) {
    if (quest_checker != nullptr) {
      if (quest_checker->GetType() == QuestType::HUNT) {
        HuntQuest* hunt_quest_checker = dynamic_cast<HuntQuest*>(quest_checker);
        if (hunt_quest_checker->GetTargetIndex() == _index) {
          hunt_quest_checker->AddCount();
          return;
        }
      }
    }
    if (checker->Next != nullptr) {
      checker = checker->Next;
    } else {
      return;
    }
  }
}

void QuestList::Open() {
  std::cout << "Quest ===="
               "============================================================"
            << std::endl
            << std::endl;
  if (Head == nullptr) {
    std::cout << "진행중인 퀘스트가 없습니다." << std::endl;
  } else {
    QuestList* node = Head;
    Quest* quest = node->quest_in_progress;
    for (int i = 0; i < Length; i++) {
      if (quest != nullptr) {
        std::cout << i + 1 << ". " << quest->GetName() << " | "
                  << quest->GetDescription() << std::endl;
        quest->PrintProgress();
      }
      node = node->Next;
    }
  }
  std::cout << std::endl
            << "============================================================="
               "========="
            << std::endl;
  Pause;
}

void QuestList::QuestComplete(Hero** player) {
  std::cout << quest_in_progress->GetName() << " 퀘스트를 완료했습니다."
            << std::endl;
  quest_in_progress->QuestComplete(player);
  delete quest_in_progress;
  Remove();
}

void QuestList::GiveUpQuest() {
  std::cout
      << quest_in_progress->GetName()
      << " 퀘스트를 포기하시겠습니까? 해당 퀘스트의 진행상황이 초기화됩니다."
      << std::endl;
  while (true) {
    std::cout << "1. 포기   2. 취소 : ";
    int is_sure = 0;
    std::cin >> is_sure;
    if (is_sure == 1) {
      delete quest_in_progress;
      Remove();
      break;
    } else if (is_sure == 2) {
      break;
    } else {
      std::cout << "잘못된 입력입니다." << std::endl;
    }
  }
}

void QuestList::RemoveAll(QuestList* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  delete head;
}

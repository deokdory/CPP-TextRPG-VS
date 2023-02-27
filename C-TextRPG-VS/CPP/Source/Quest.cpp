#include "Quest.h"

#include "pch.h"

Quest::Quest()
    : index(0), name("null"), description("null"), type(QuestType::NONE) {}
Quest::Quest(int index, std::string name, std::string description,
             QuestType type)
    : index(0), name(name), description(description), type(type) {}

void Quest::SetIsCompleted(bool _is_completed) { is_completed = _is_completed; }

void Quest::SetRewardExp(int _reward_exp) { reward_exp = _reward_exp; }
void Quest::SetRewardGold(int _reward_gold) { reward_gold = _reward_gold; }

void Quest::QuestComplete(Hero** player) {
  for (int i = 0; i < PARTY_MAX; i++) {
    if (player[i] != nullptr) {
      player[i]->GiveExp(reward_exp);
      GameManager::AddGold(reward_gold);
    }
  }
  SetIsCompleted();
}

HuntQuest::HuntQuest(int _index, std::string _name, std::string _description,
                     QuestType _type, int _target_enemy_index,
                     int _target_enemy_goal, int _count)
    : Quest(_index, name, description, _type),
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
  std::cout << Enemy::GetNameWithIndex(target_enemy_index) << "»ç³É : " << count
            << " / " << target_enemy_goal << " (" << progress_percent << "%)"
            << std::endl;
}

SupplyQuest::SupplyQuest(int _index, std::string _name,
                         std::string _description, QuestType _type,
                         int _required_item_index, int _required_item_count,
                         int count)
    : Quest(_index, _name, _description, _type),
      required_item_index(_required_item_index),
      required_item_count(_required_item_count),
      count(count) {}

SupplyQuest::SupplyQuest(int _index, std::string _name,
                         std::string _description, QuestType _type,
                         int _required_item_index, int _required_item_count)
    : Quest(_index, _name, _description, _type),
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

bool SupplyQuest::IsGoalAchieved() {
  bool is_goal_achieved = false;
  if (count >= required_item_count) is_goal_achieved = true;
  return is_goal_achieved;
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
            << "Àü´Þ : " << count << " / " << required_item_count << " ("
            << progress_percent << "%)" << std::endl;
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

  Quest* NewQuest(int _index) {
    if (1 <= _index && _index <= 1000)
      return NewHuntQuest(_index);
    else if (1001 <= _index && _index <= 2000)
      return NewSupplyQuest(_index);
  }

  Quest* NewHuntQuest(int _index) {
    std::string name = "NULL";
    std::string description = "NULL";
    QuestType type = QuestType::HUNT;
    int target_enemy_index = 0;
    int target_enemy_goal = 0;
    switch (_index) {
      type = QuestType::HUNT;
      case 1: {
        name = "´Á´ë Àâ±â";
        description = "´Á´ë ¹«¼­¿ö 5¸¶¸® Àâ¾ÆÁà";
        target_enemy_index = WOLF;
        target_enemy_goal = 5;
        break;
      }
      default: {
        std::cout << "ERROR:Undefined Quest Index" << std::endl;
        system("pause");
        return nullptr;
      }
    }
    return new HuntQuest(_index, name, description, type, target_enemy_index,
                         target_enemy_goal);
  }

  Quest* NewSupplyQuest(int _index) {
    std::string name = "NULL";
    std::string description = "NULL";
    QuestType type = QuestType::HUNT;
    int target_item_index = 0;
    int target_item_goal = 0;
    switch (_index) {
      case 1001: {
        name = "´Á´ë ÀÌ»¡ °®°í ½Í¾î";
        description = "´Á´ë ÀÌ»¡ÀÌ ÇÊ¿äÇØ 3°³ °®´ÙÁà";
        target_item_index = WOLF_TOOTH;
        target_item_goal = 3;
        break;
      }
      default: {
        std::cout << "ERROR:Undefined Quest Index" << std::endl;
        system("pause");
        return nullptr;
      }
    }
    return new SupplyQuest(_index, name, description, type, target_item_index,
                           target_item_goal);
  }

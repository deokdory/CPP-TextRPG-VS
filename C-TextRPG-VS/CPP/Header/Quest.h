#pragma once
#include "Character.h"
#include "Item.h"

enum class QuestType { HUNT, SUPPLY, GOTO };

class Quest {
 public:
  std::string GetName() const { return name; }
  std::string GetDescription() const { return description; }
  QuestType GetType() const { return type; }

  bool GetIsCompleted() const { return is_completed; }
  void SetIsCompleted(bool _is_completed = true);

  int GetRewardExp() const { return reward_exp; }
  int GetRewardGold() const { return reward_gold; }

  void SetRewardExp(int);
  void SetRewardGold(int);

  virtual void PrintProgress() = 0;

 protected:
  std::string name;
  std::string description;
  QuestType type;

  bool is_completed;

  int reward_exp;
  int reward_gold;
  Item* reward_item;
};

class HuntQuest : public Quest {
 public:
  int GetTargetIndex() const { return target_enemy_index; }
  int GetObjectiveCount() const { return target_enemy_goal; }
  int GetCount() const { return count; }

  bool IsGoalAchieved();

  void SetTargetEnemyIndex(int);
  void SetObjectiveCount(int);

  void AddCount();

  virtual void PrintProgress();

 private:
  int target_enemy_index;
  int target_enemy_goal;
  int count;
};

class SupplyQuest : public Quest {
 public:
  int GetRequiredItemIndex() const { return required_item_index; }
  int GetRequiredItemCount() const { return required_item_count; }
  int GetCount() const { return count; }

  bool IsGoalAchieved();

  void SetRequiredItemIndex(int);
  void SetRequiredItemCount(int);
  void AddCount();

  virtual void PrintProgress();

 private:
  int required_item_index;
  int required_item_count;
  int count;
};
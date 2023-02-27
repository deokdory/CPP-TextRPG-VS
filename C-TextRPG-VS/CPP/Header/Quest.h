#pragma once
#include "Character.h"
#include "Item.h"
#include "GameManager.h"

enum class QuestType { NONE, HUNT, SUPPLY, GOTO };

// index 0001 ~ 1000 : 사냥퀘스트
// index 1001 ~ 2000 : 보급퀘스트

class Quest {
 public:
  Quest();
  Quest(int index, std::string name, std::string description, QuestType type);

  int GetIndex() const { return index; }
  std::string GetName() const { return name; }
  std::string GetDescription() const { return description; }
  QuestType GetType() const { return type; }
   
  bool GetIsCompleted() const { return is_completed; }
  void SetIsCompleted(bool _is_completed = true);

  int GetRewardExp() const { return reward_exp; }
  int GetRewardGold() const { return reward_gold; }

  void SetRewardExp(int);
  void SetRewardGold(int);

  virtual bool IsGoalAchieved() = 0;
  virtual void AddCount() = 0;
  virtual void PrintProgress() = 0;

  virtual void QuestComplete(Hero**);

 protected:
  int index;
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
  HuntQuest(int _index, std::string _name, std::string _description,
            QuestType _type, int _target_enemy_index, int _target_enemy_goal, int _count = 0);

  int GetTargetIndex() const { return target_enemy_index; }
  int GetObjectiveCount() const { return target_enemy_goal; }
  int GetCount() const { return count; }

  void SetTargetEnemyIndex(int);
  void SetObjectiveCount(int);

  virtual bool IsGoalAchieved();
  virtual void AddCount();
  virtual void PrintProgress();

  virtual void QuestComplete(Hero**);

 private:
  int target_enemy_index;
  int target_enemy_goal;
  int count;
};

class SupplyQuest : public Quest {
 public:
  SupplyQuest(int _index, std::string _name, std::string _description,
              QuestType _type, int target_item_index, int target_item_goal);
  int GetRequiredItemIndex() const { return required_item_index; }
  int GetRequiredItemCount() const { return required_item_count; }
  int GetCount() const;


  virtual bool IsGoalAchieved();

  void SetRequiredItemIndex(int);
  void SetRequiredItemCount(int);

  virtual void PrintProgress();

  virtual void QuestComplete(Hero**);

 private:
  int required_item_index;
  int required_item_count;
};

Quest* NewQuest(int _index);
Quest* NewHuntQuest(int _index);
Quest* NewSupplyQuest(int _index);

class QuestList {
 public:
  // Linked List 기본 멤버
  static QuestList* NewQuestList(int _index);
  void Push();

  void Remove();
  void static RemoveAll();

  // ==========================
  void Open();

  static const int GetHighestLvlOfPlayer(
      Hero**);  // 히어로 포인터배열을 전달받아 가장 높은 레벨을 구함
  void QuestComplete(Hero**);
  void GiveUpQuest();

 private:
  Quest* quest_in_progress;

  static QuestList* Head;
  static QuestList* Tail;

  QuestList* Next;
  QuestList* Prev;

  static int Length;
};
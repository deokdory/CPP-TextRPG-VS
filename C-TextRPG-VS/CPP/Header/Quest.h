#pragma once
#include "Character.h"
#include "GameManager.h"
#include "Item.h"

enum class QuestType { NONE, HUNT, GOTO };

// index 0001 ~ 1000 : 사냥퀘스트

class Quest {
 public:
  Quest(int index, std::string name, std::string description, QuestType type,
        int reward_exp, int reward_gold, Item* reward_item = nullptr);

  int GetIndex() const { return index; }
  std::string GetName() const { return name; }
  std::string GetDescription() const { return description; }
  QuestType GetType() const { return type; }

  int GetRewardExp() const { return reward_exp; }
  int GetRewardGold() const { return reward_gold; }

  virtual bool IsGoalAchieved() = 0;
  virtual void AddCount() = 0;
  virtual void PrintProgress() = 0;

  virtual void QuestComplete(Hero**);

 protected:
  int index;
  std::string name;
  std::string description;
  QuestType type;

  int reward_exp;
  int reward_gold;
  Item* reward_item;
};

class HuntQuest : public Quest {
 public:
  HuntQuest(int _index, std::string _name, std::string _description,
            QuestType _type, int _reward_exp, int _reward_gold,
            int _target_enemy_index, int _target_enemy_goal, int _count = 0,
            Item* _reward_item = nullptr);

  int GetTargetIndex() const { return target_enemy_index; }
  int GetObjectiveCount() const { return target_enemy_goal; }
  int GetCount() const { return count; }

  void SetTargetEnemyIndex(int);
  void SetObjectiveCount(int);

  virtual bool IsGoalAchieved();
  virtual void AddCount();
  virtual void PrintProgress();

 private:
  int target_enemy_index;
  int target_enemy_goal;
  int count;
};

class SupplyQuest : public Quest {
 public:
  SupplyQuest(int _index, std::string _name, std::string _description,
              QuestType _type, int reward_exp, int reward_gold,
              int target_item_index, int target_item_goal,
              Item* reward_item = nullptr);
  int GetRequiredItemIndex() const { return required_item_index; }
  int GetRequiredItemCount() const { return required_item_count; }
  int GetCount() const;

  virtual bool IsGoalAchieved();

  void SetRequiredItemIndex(int);
  void SetRequiredItemCount(int);

  virtual void PrintProgress();

  // 보급 퀘스트에선 사용하지 않음
  virtual void AddCount();

  virtual void QuestComplete(Hero**);

 private:
  int required_item_index;
  int required_item_count;
};

#define MAX_QUEST_IN_PROGRESS 5

Quest* NewQuest(int _index);
Quest* NewHuntQuest(int _index);
//Quest* NewSupplyQuest(int _index);

class QuestList {
 public:
  // Linked List 기본 멤버
  QuestList(int _index);

  static void QuestCompleteChecker(Hero** Player);

  static void NewQuestList(int _index);
  void Push();

  static const QuestList* GetHead() { return Head; }
  QuestList* GetNext() const { return Next; }

  static const int GetLength() { return Length; }

  void Remove();
  void static RemoveAll();

  static void HuntQuestProgressChecker(int _index);
  // ==========================
  static void Open();

  void QuestComplete(Hero**);
  Quest* GetQuestInProgress() { return quest_in_progress; }
  void GiveUpQuest();

 private:
  static void RemoveAll(QuestList* head);

  Quest* quest_in_progress;

  static QuestList* Head;
  static QuestList* Tail;

  QuestList* Next;
  QuestList* Prev;

  static int Length;
};

class CompletedQuest {
 public:
  CompletedQuest(int _index);

  static void NewCompletedQuest(int _index);
  void Push();

  static bool CheckIsCompletedQuest(int _index);

 private:
  int completed_quest_index;

 private:
  static CompletedQuest* Head;
  static CompletedQuest* Tail;
  static int Length;

  CompletedQuest* Next;

  int GetCompletedQuestIndex() const { return completed_quest_index; }

  void Remove();
  void RemoveAll(CompletedQuest* node = Head);
};
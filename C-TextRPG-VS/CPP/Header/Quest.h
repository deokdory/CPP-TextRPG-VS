#pragma once

enum class QuestType { HUNT, BRING_ITEM, GOTO };

class Quest {
 public:
   void PrintDialogue() const;

  std::string GetName() const;
  std::string GetDescription() const;
  QuestType GetType() const;
  
 protected:
  std::string name;
  std::string description;
  QuestType type;
};

class HuntQuest : public 
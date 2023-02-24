#include "pch.h"
#include "Quest.h"

bool Quest::SetIsCompleted(bool _is_completed) { is_completed = _is_completed; }

void Quest::SetRewardExp(int _reward_exp) { reward_exp = _reward_exp; }
void Quest::SetRewardGold(int _reward_gold) { reward_gold = _reward_gold; }

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
  double progress_percent = count / target_enemy_goal * 100;
  std::cout << Enemy::GetNameWithIndex(target_enemy_index)
            << "����ϱ� : " << count << " / " << target_enemy_goal << " ("
            << progress_percent << "%)" << std::endl;
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

void SupplyQuest::AddCount() { count++; }

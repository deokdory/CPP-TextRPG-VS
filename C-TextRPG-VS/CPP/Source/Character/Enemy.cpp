#include "pch.h"
#include "Enemy.h"



Enemy::Enemy(std::string _name, int _lvl)
    : Character::Character(_name, _lvl),
      reward_gold(GetRewardGoldForCurrentLvl()),
      reward_exp(GetRewardExpForCurrentLvl()) {}

int Enemy::GetRewardGold() const { return reward_gold; }

int Enemy::GetRewardExp() const { return reward_exp; }

int Enemy::GetRewardGoldForCurrentLvl() {
  int reward_gold_per_lvl[CHARACTER_LVL_MAX] = {20,  40,  60,  80,  100,
                                                120, 140, 160, 180, 200};
  return reward_gold_per_lvl[lvl];
}

int Enemy::GetRewardExpForCurrentLvl() {
  int reward_exp_per_lvl[CHARACTER_LVL_MAX] = {10, 15, 20, 25, 30,
                                               35, 40, 45, 50, 100};
  return reward_exp_per_lvl[lvl];
}
#include "pch.h"
#include "Character.h"

#define ENEMY_STAT_ADJUST 0.9

Enemy::Enemy() : Character::Character(), reward_gold(0), reward_exp(0) {}

Enemy::Enemy(std::string _name, int _lvl)
    : Character::Character(_name, _lvl, 0.9),
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

void Enemy::PrintStatus(short x) {
  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;
  PrintHp();
  PrintHpBar();
  ENDL;

  gotox(x);
  PrintAtk();
  PrintDef();
  PrintSpd();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  std::cout << "                        ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

void Enemy::PrintStatus(short x, short y) {
  gotoxy(x, y);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;
  PrintHp();
  PrintHpBar();
  ENDL;

  gotox(x);
  PrintAtk();
  PrintDef();
  PrintSpd();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  std::cout << "                        ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}
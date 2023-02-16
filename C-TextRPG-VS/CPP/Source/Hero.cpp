#include "pch.h"
#include "Hero.h"

int Hero::gold = 0;

Hero::Hero() : Character::Character(), exp(0) {
  max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(std::string _name, int _lvl)
    : Character::Character(_name, _lvl), exp(0) {
  max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(const Hero& other)
    : Character::Character(other), exp(other.exp), max_exp(other.max_exp) {}

int Hero::GetMaxExpForCurrentLvl() const {
  int max_exp_for_each_lvl[CHARACTER_LVL_MAX - 1] = {20, 30, 40, 50, 60,
                                                     70, 80, 90, 100};
  return max_exp_for_each_lvl[Character::GetLvl() - 1];
}

void Hero::PrintStatus() { Character::PrintStatus();
  std::cout << "exp : " << exp << " / " << max_exp << std::endl;
  std::cout << "gold : " << gold << std::endl;
}

  Hero::~Hero() {}
#include "pch.h"
#include "Hero.h"

Hero::Hero() : Character::Character(), exp(0) {
  max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(std::string _name, int _lvl)
    : Character::Character(_name, _lvl), exp(0) {
  max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(const Hero& other)
    : Character::Character(other), exp(other.exp), max_exp(other.max_exp) {}

int Hero::GetGold() const { return gold; }
void Hero::SetGold(int _gold) { gold += _gold; }

int Hero::GetMaxExpForCurrentLvl() const {
  int max_exp_for_each_lvl[CHARACTER_LVL_MAX - 1] = {20, 30, 40, 50, 60,
                                                     70, 80, 90, 100};
  return max_exp_for_each_lvl[Character::GetLvl() - 1];
}

void Hero::GiveExp(int _exp) {
  int prev_lvl = GetLvl();
  exp += _exp;
  std::cout << "경험치를 " << exp << "만큼 얻었다!" << std::endl;
  SYSTEM_MESSAGE_DELAY;
  while (true) {
    if (exp >= max_exp) {
      LvlUp();
      exp -= max_exp;
      max_exp = GetMaxExpForCurrentLvl();
    } else {
      break;
    }
  }
}

void Hero::PrintStatus() {
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << Character::GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;
  RESET_FORMAT;
  PrintHp();
  PrintHpBar();
  ENDL;
  Character::PrintAtk();
  Character::PrintDef();
  Character::PrintSpd();
  std::cout << std::endl;
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;
  PrintExp();
  std::cout << "           ";
  Character::PrintLvl();
  ENDL;
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

void Hero::PrintExp() {
  std::cout << "EXP ";
  SET_FORMAT_WIDTH_R(3);
  std::cout << exp;
  RESET_FORMAT;
  std::cout << " / ";
  SET_FORMAT_WIDTH_L(3);
  std::cout << max_exp;
  RESET_FORMAT;

}

Hero::~Hero() {}
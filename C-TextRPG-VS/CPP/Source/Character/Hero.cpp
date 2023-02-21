#include "pch.h"
#include "Hero.h"

Hero::Hero() : Character::Character(), exp(0), skills(new Skill[HERO_SKILL_MAX]) {
	max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(std::string _name, int _lvl)
	: Character::Character(_name, _lvl), exp(0), skills(new Skill[HERO_SKILL_MAX]) {
	max_exp = GetMaxExpForCurrentLvl();
}

Hero::Hero(const Hero& other)
	: Character::Character(other), exp(other.exp), max_exp(other.max_exp) {
  skills = new Skill(*other.skills);
}

int Hero::GetMaxExpForCurrentLvl() const {
	int max_exp_for_each_lvl[CHARACTER_LVL_MAX - 1] = { 20, 30, 40, 50, 60,
													   70, 80, 90, 100 };
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
		}
		else {
			break;
		}
	}
}

void Hero::PrintStatus(short x) {
  gotox(x);
	for (int i = 0; i < STATUS_LENGTH; i++) {
		std::cout << "=";
	}
	ENDL;

  gotox(x);
	SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
	std::cout << Character::GetName();
	RESET_FORMAT;
	SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
	std::cout << GetClass() << std::endl;

  gotox(x);
	RESET_FORMAT;
	PrintHp();
	PrintHpBar();
	ENDL;

	gotox(x);
	Character::PrintAtk();
	Character::PrintDef();
	Character::PrintSpd();
  ENDL;

	gotox(x);
	for (int i = 0; i < STATUS_LENGTH; i++) {
		std::cout << "-";
	}
	ENDL;
	
	gotox(x);
	PrintExp();
	std::cout << "           ";
	Character::PrintLvl();
	ENDL;

	gotox(x);
	for (int i = 0; i < STATUS_LENGTH; i++) {
		std::cout << "=";
	}
	ENDL;
}

void Hero::PrintStatus(short x, short y) {
  gotoxy(x, y);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
    gotox(0);
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << Character::GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;
  PrintHp();
  PrintHpBar();
  ENDL;

  gotox(x);
  Character::PrintAtk();
  Character::PrintDef();
  Character::PrintSpd();
  ENDL;
  gotox(x);

  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  PrintExp();
  std::cout << "           ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
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

Hero::~Hero() {
  if (skills != nullptr) {
    delete[] skills;
  }
}
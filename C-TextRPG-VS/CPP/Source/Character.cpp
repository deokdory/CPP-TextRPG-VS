#include "pch.h"
#include "Character.h"

int Character::num_of_character = 0;

Character::Character()
    : name("CHARACTER"),
      class_of_character(Class::COMMON),
      max_hp(COMMON_MAXHP_ORIGIN),
      hp(max_hp),
      atk(COMMON_ATK_ORIGIN),
      def(COMMON_DEF_ORIGIN),
      spd(COMMON_SPD_ORIGIN),
      lvl(1),
      is_dead(false) {
  //std::cout << "기본 생성자 호출" << std::endl;
  num_of_character++;
}

Character::Character(std::string _name, int _lvl)
    : name(_name),
      class_of_character(Class::COMMON),
      lvl(_lvl),
      is_dead(false) {
  //std::cout << "매개변수 생성자 호출" << std::endl;
  int lvl_for_stat = 0;
  if (_lvl > 0) {
    lvl_for_stat = _lvl - 1;
  } else if (_lvl > 10) {
    std::cout << "ERROR : over level max" << std::endl;
    lvl_for_stat = 10;
  } else {
    std::cout << "ERROR : lvl out of range" << std::endl;
    lvl_for_stat = 1;
  }
  max_hp = COMMON_MAXHP_ORIGIN + COMMON_MAXHP_PER_LVL * lvl_for_stat;
  hp = max_hp;
  atk = COMMON_ATK_ORIGIN + COMMON_ATK_PER_LVL * lvl_for_stat;
  def = COMMON_DEF_ORIGIN + COMMON_DEF_PER_LVL * lvl_for_stat;
  spd = COMMON_SPD_ORIGIN + COMMON_SPD_PER_LVL * lvl_for_stat;
  num_of_character++;
}

Character::Character(const Character& _hero)
    : name(_hero.name),
      class_of_character(_hero.class_of_character),
      max_hp(_hero.max_hp),
      hp(_hero.hp),
      atk(_hero.atk),
      def(_hero.def),
      spd(_hero.spd),
      lvl(_hero.lvl),
      is_dead(_hero.is_dead) {
  //std::cout << "복사 생성자 호출" << std::endl;
  num_of_character++;
}

std::string Character::GetClass() const {
  std::string class_name;
  switch (class_of_character) {
    case Class::COMMON:
      class_name = "COMMON";
      break;
    case Class::WARRIOR:
      class_name = "WARRIOR";
      break;
    case Class::ARCHOR:
      class_name = "ARCHOR";
      break;
    case Class::THIEF:
      class_name = "THIEF";
      break;
    default:
      std::cout << "ERROR : no class like that" << std::endl;
  }
  return class_name;
}

int Character::GetLvl() const { return lvl; }

void Character::PrintTotalCharacter() {
  std::cout << "total character : " << num_of_character << std::endl;
}

void Character::PrintStatus() {
  for (int i = 0; i < HP_BAR_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
  std::cout << "name : ";
  SET_FORMAT_WIDTH_L(15);
  std::cout << name;
  RESET_FORMAT;
  std::cout << "lvl : ";
  SET_FORMAT_WIDTH_R(2);
  std::cout << lvl << std::endl;
  RESET_FORMAT;
  PrintHp();
  SET_FORMAT_WIDTH_R(16);
  std::cout << GetClass() << std::endl;
  RESET_FORMAT;
  PrintHpBar();
  ENDL;
  std::cout << "ATK ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << atk;
  RESET_FORMAT;
  std::cout << "DEF ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << def;
  RESET_FORMAT;
  std::cout << "SPD ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << spd;
  RESET_FORMAT;
  std::cout << std::endl;
  for (int i = 0; i < HP_BAR_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

double Character::GetHpRemain() const {
  if (max_hp != 0) {
    return (hp / max_hp) * 100;
  } else {
    std::cout << "ERROR : max_hp == 0!!" << std::endl;
    return 0;
  }
}

void Character::PrintHp() const {
  std::cout << "HP : ";
  SET_FORMAT_WIDTH_R(3);
  std::cout << hp;
  RESET_FORMAT;
  std::cout << " / ";
  SET_FORMAT_WIDTH_L(3);
  std::cout << max_hp;
  RESET_FORMAT;
  //SET_FORMAT_2PREC;
  //std::cout << GetHpRemain() << "%)";
  //RESET_FORMAT;
}

void Character::PrintHpBar() const {
  float hp_per_box;
  if (HP_BAR_LENGTH) {
    hp_per_box = 100 / HP_BAR_LENGTH;
  } else {
    printf("ERROR : HP_BAR_LENGTH = 0!!");
  }
  for (int i = 1; i <= HP_BAR_LENGTH; i++) {
    if ((int)GetHpRemain() > hp_per_box * i) {
      printf("■");
    } else {
      printf("□");
    }
  }
}

Character::~Character() {
  //std::cout << "캐릭터 수 감소" << std::endl;
  num_of_character--;
}
#include "stdafx.h"
#include "Character.h"
 
int Character::num_of_character = 0;

Character::Character()
    : name("NAME"),
      class_of_character(Class::COMMON),
      max_hp(COMMON_MAXHP_ORIGIN),
      hp(max_hp),
      atk(COMMON_ATK_ORIGIN),
      def(COMMON_DEF_ORIGIN),
      spd(COMMON_SPD_ORIGIN),
      lvl(1),
      is_dead(false) {
  num_of_character++;
}

Character::Character(std::string _name, int _lvl)
    : name(_name), class_of_character(Class::COMMON), lvl(_lvl), is_dead(false) {
  int lvl_for_stat = 0;
  if (_lvl > 0) {
    lvl_for_stat = _lvl - 1;
  } else {
    std::cout << "ERROR : cannot create character for 0 lvl" << std::endl;
    lvl_for_stat = 1;
  }
  max_hp = COMMON_MAXHP_ORIGIN + COMMON_MAXHP_PER_LVL * lvl_for_stat;
  hp = max_hp;
  atk = COMMON_ATK_ORIGIN + COMMON_ATK_PER_LVL * lvl_for_stat;
  def = COMMON_DEF_ORIGIN + COMMON_DEF_PER_LVL * lvl_for_stat;
  spd = COMMON_SPD_ORIGIN + COMMON_SPD_PER_LVL * lvl_for_stat;
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

void Character::PrintStatus() {
  std::cout << "name : " << name << "\tclass : " << GetClass() << std::endl;
  std::cout << "hp : " << hp << " / " << max_hp << std::endl;
  std::cout << "atk : " << atk << "\tdef : " << def << "\tspd : " << spd
            << std::endl;
  std::cout << "lvl : " << lvl << "\t\tis_dead : " << is_dead << endll;
}

Character::~Character() {}

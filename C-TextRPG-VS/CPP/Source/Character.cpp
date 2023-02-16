#include "pch.h"
#include "Character.h"

int Character::num_of_character = 0;

Character::Character()
    : name("Character"),
      class_of_character(Class::COMMON),
      max_hp(COMMON_MAXHP_ORIGIN),
      hp(max_hp),
      atk(COMMON_ATK_ORIGIN),
      def(COMMON_DEF_ORIGIN),
      spd(COMMON_SPD_ORIGIN),
      lvl(1),
      is_dead(false) {
  //std::cout << "�⺻ ������ ȣ��" << std::endl;
  num_of_character++;
}

Character::Character(std::string _name, int _lvl)
    : class_of_character(Class::COMMON),
      lvl(_lvl),
      is_dead(false) {
  //std::cout << "�Ű����� ������ ȣ��" << std::endl;
  if (_name.length() > NAME_LIMIT) {
    std::cout << "ERROR : name out of range (name limit : " << NAME_LIMIT << ")" << std::endl;
    _name = "Character";
  }
  name = _name;
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
  //std::cout << "���� ������ ȣ��" << std::endl;
  num_of_character++;
}

void Character::LvlUp() {
  lvl++;
  max_hp += COMMON_MAXHP_PER_LVL;
  hp += COMMON_MAXHP_PER_LVL;
  atk += COMMON_ATK_PER_LVL;
  def += COMMON_DEF_PER_LVL;
  spd += COMMON_SPD_PER_LVL;
  std::cout << name << "�� ������ �ö���!" << std::endl;
  SYSTEM_MESSAGE_DELAY;
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

std::string Character::GetName() const { return name; }

void Character::SetMaxHp(int _max_hp) { max_hp = _max_hp; }
void Character::SetHp(int _hp) { hp = _hp; }
void Character::SetAtk(int _atk) { atk = _atk; }
void Character::SetDef(int _def) { def = _def; }
void Character::SetSpd(int _spd) { spd = _spd; }
void Character::SetLvl(int _lvl) { lvl = _lvl; }

int Character::GetMaxHp() const { return max_hp; }
double Character::GetHp() const { return hp; }
int Character::GetAtk() const { return atk; }
int Character::GetDef() const { return def; }
int Character::GetSpd() const { return spd; }
int Character::GetLvl() const { return lvl; }
bool Character::IsDead() const { return false; }

void Character::PrintTotalCharacter() {
  std::cout << "total character : " << num_of_character << std::endl;
}

void Character::PrintStatus() {
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;
  RESET_FORMAT;

  PrintHp();
  PrintHpBar();
  ENDL;
  PrintAtk();
  PrintDef();
  PrintSpd();
  ENDL;
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;
  std::cout << "                        ";
  Character::PrintLvl();
  ENDL;
  for (int i = 0; i < STATUS_LENGTH; i++) {
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
  std::cout << "HP ";
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
      printf("��");
    } else {
      printf("��");
    }
  }
}

void Character::PrintAtk() const {
  std::cout << "ATK ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << GetAtk();
  RESET_FORMAT;
}

void Character::PrintDef() const {
  std::cout << "DEF ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << GetDef();
  RESET_FORMAT;
}

void Character::PrintSpd() const {
  std::cout << "SPD ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << GetSpd();
  RESET_FORMAT;
}

void Character::PrintLvl() const {
  std::cout << "lvl ";
  SET_FORMAT_WIDTH_R(2);
  std::cout << GetLvl();
  RESET_FORMAT;
}

Character::~Character() {
  //std::cout << "ĳ���� �� ����" << std::endl;
  num_of_character--;
}
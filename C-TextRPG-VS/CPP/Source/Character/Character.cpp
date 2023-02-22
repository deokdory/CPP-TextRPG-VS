#include "pch.h"
#include "Character.h"

Character::Character()
    : name("Character"),
      class_of_character(Class::COMMON),
      max_hp(COMMON_MAXHP_ORIGIN),
      hp(max_hp),
      atk(COMMON_ATK_ORIGIN),
      def(COMMON_DEF_ORIGIN),
      spd(COMMON_SPD_ORIGIN),
      lvl(1),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  //std::cout << "기본 생성자 호출" << std::endl;
}

Character::Character(std::string _name, int _lvl)
    : class_of_character(Class::COMMON),
      lvl(_lvl),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  //std::cout << "매개변수 생성자 호출" << std::endl;
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
}

Character::Character(std::string _name, int _lvl, double _adjust)
    : class_of_character(Class::COMMON),
      lvl(_lvl),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  // std::cout << "매개변수 생성자 호출" << std::endl;
  if (_name.length() > NAME_LIMIT) {
    std::cout << "ERROR : name out of range (name limit : " << NAME_LIMIT << ")"
              << std::endl;
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
  max_hp =
      (COMMON_MAXHP_ORIGIN + COMMON_MAXHP_PER_LVL * lvl_for_stat) * _adjust;
  hp = max_hp;
  atk = (COMMON_ATK_ORIGIN + COMMON_ATK_PER_LVL * lvl_for_stat) * _adjust;
  def = (COMMON_DEF_ORIGIN + COMMON_DEF_PER_LVL * lvl_for_stat) * _adjust;
  spd = (COMMON_SPD_ORIGIN + COMMON_SPD_PER_LVL * lvl_for_stat) * _adjust;
}

Character::Character(const Character& other)
    : name(other.name),
      class_of_character(other.class_of_character),
      max_hp(other.max_hp),
      hp(other.hp),
      atk(other.atk),
      def(other.def),
      spd(other.spd),
      lvl(other.lvl),
      turn_spd(other.turn_spd),
      turn_waiter(other.turn_waiter),
      is_dead(other.is_dead) {
  //std::cout << "복사 생성자 호출" << std::endl;
}

void Character::LvlUp() {
  lvl++;
  max_hp += COMMON_MAXHP_PER_LVL;
  hp += COMMON_MAXHP_PER_LVL;
  atk += COMMON_ATK_PER_LVL;
  def += COMMON_DEF_PER_LVL;
  spd += COMMON_SPD_PER_LVL;
  std::cout << name << "의 레벨이 올랐다!" << std::endl;
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
void Character::SetHp(int _hp) {
  if (_hp > max_hp) {
    _hp = max_hp;
  }
  hp = _hp;
}
void Character::SetAtk(int _atk) { atk = _atk; }
void Character::SetDef(int _def) { def = _def; }
void Character::SetSpd(int _spd) { spd = _spd; }
void Character::SetLvl(int _lvl) {
  if (_lvl > CHARACTER_LVL_MAX) {
    _lvl = CHARACTER_LVL_MAX;
  }
  lvl = _lvl;
}

void Character::SetTurnSpd(double _turn_spd) { turn_spd = _turn_spd; }
void Character::SetTurnWaiter(double _turn_waiter) {
  turn_waiter = _turn_waiter;
}

void Character::AddTurnWaiter(double _turn_waiter) {
  turn_waiter += _turn_waiter;
}

void Character::Attack(Character& target) {
    int damage = 0;
    std::cout << name << "가 " << target.name << "을 공격하려고 한다";
    for (int i = 0; i < 3; i++) {
        printf(" .");
        Sleep(500);
    }
    if (damage = atk - target.def < 0) {
        damage = 0;
    }

    target.hp -= damage; 
    std::cout << target.name << "은 " << damage << "의 피해를 입었다" << std::endl;
    SYSTEM_MESSAGE_DELAY;

    //
//    if(!(target.CheckIsDead())) {
//        std::cout << target.name << "은 반격했다";
//        for (int i = 0; i < 3; i++) {
//            printf(" .");
//            Sleep(500);
//        }
//        if (damage = target.atk - def < 0) {
//            damage = 0;
//       
//        hp -= damage;
//
//        std::cout << name << "은 " << damage << "의 피해를 입었다" << std::endl;
//        SYSTEM_MESSAGE_DELAY;
//        CheckIsDead();
//        }
//    }
}

void Character::BoostMaxHp(int _amount, int duration) {
  if (duration) {
    max_hp = _amount;
  }
}

void Character::BoostAtk(int _amount, int duration) {
  if (duration) {
    atk += _amount;
  }
}
void Character::BoostDef(int _amount, int duration) {
  if (duration) {
    def += _amount;
  }
}
void Character::BoostSpd(int _amount, int duration) {
  if (duration) {
    spd += _amount;
  }
}

bool Character::CheckIsDead() {
    if (!is_dead) {
        if (hp <= 0) {
            hp = 0;
            is_dead = true;
            std::cout << name << "은 쓰러졌다." << std::endl;
            SYSTEM_MESSAGE_DELAY;
        }
    } return is_dead;
}

int Character::GetMaxHp() const { return max_hp; }
double Character::GetHp() const { return hp; }
int Character::GetAtk() const { return atk; }
int Character::GetDef() const { return def; }
int Character::GetSpd() const { return spd; }
int Character::GetLvl() const { return lvl; }

double Character::GetTurnSpd() const { return turn_spd; }

double Character::GetTurnWaiter() const { return turn_waiter; }

void Character::PrintStatus(short x) {
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

void Character::PrintStatus(short x, short y) {
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
      printf("■");
    } else {
      printf("□");
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
  //std::cout << "캐릭터 수 감소" << std::endl;
}

void NewPlayerCharacter(Hero** _Player) {
  int slot = GetNumOfPlayableHeroes(_Player);
  if (slot < PARTY_MAX) {
    std::string name;
    while (true) {
      system("cls");

      std::string temp;
      std::cout << "이름? : ";
      std::cin >> temp;

      if (temp.length() > NAME_LIMIT) {
        std::cout << "이름 길이 제한은 영어" << NAME_LIMIT << "자, 한글 "
                  << NAME_LIMIT / 2 << "자 입니다." << std::endl;
        SYSTEM_MESSAGE_DELAY;
      } else {
        name = temp;
        break;
      }
    }
    _Player[slot] = new Hero(name, 1);
  }
}

void PlayerArrayAlign(Hero** Player) {
  for (int i = 0; i < PARTY_MAX; i++) {
    for (int j = i + 1; j < PARTY_MAX; j++) {
      if (Player[i] == nullptr && Player[j] != nullptr) {
        Swap(Player[i], Player[j]);
      }
    }
  }
}

int GetNumOfPlayableHeroes(Hero** _Player) {
  int num_of_playble_heroes = 0;
  for (int i = 0; i < PARTY_MAX; i++) {
    if (_Player[i] != nullptr) {
      num_of_playble_heroes++;
    } else {
      break;
    }
  }
  return num_of_playble_heroes;
}

void Swap(Hero* _Hero1, Hero* _Hero2) {
  Hero* temp = _Hero1;
  _Hero1 = _Hero2;
  _Hero2 = temp;
}

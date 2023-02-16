#pragma once

#define PARTY_MAX 4  // 파티 최대 인원 (아군, 적군 공통)

#define NAME_LIMIT 12
#define CLASS_TOTAL 4

#define SET_FORMAT_WIDTH_L(length) \
  std::cout << std::setw(length) << std::setiosflags(std::ios::left)
#define SET_FORMAT_WIDTH_R(length) \
  std::cout << std::setw(length) << std::setiosflags(std::ios::right)
#define SET_FORMAT_2PREC \
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2)

#define COMMON_MAXHP_ORIGIN 50
#define COMMON_ATK_ORIGIN 25
#define COMMON_DEF_ORIGIN 10
#define COMMON_SPD_ORIGIN 10

#define COMMON_MAXHP_PER_LVL 5
#define COMMON_ATK_PER_LVL 5
#define COMMON_DEF_PER_LVL 5
#define COMMON_SPD_PER_LVL 5

#define CHARACTER_LVL_MAX 10

#define HP_BAR_LENGTH 30

enum class Class {
  COMMON,
  WARRIOR,
  ARCHOR,
  THIEF,
};

class Character {

  std::string name;
  Class class_of_character;

  int max_hp;
  double hp;
  int atk;
  int def;
  int spd;

  int lvl;

  bool is_dead;

 protected:
  static int num_of_character;

 public:

  Character();
  Character(std::string _name, int _lvl);
  Character(const Character& other);

  std::string GetClass() const;
  int GetLvl() const;

  static void PrintTotalCharacter();

  virtual void PrintStatus();
  double GetHpRemain() const;
  void PrintHp() const;
  void PrintHpBar() const;

  virtual ~Character();
};
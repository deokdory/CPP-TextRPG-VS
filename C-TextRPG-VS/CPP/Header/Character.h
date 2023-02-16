#pragma once

#define PARTY_MAX 4  // 파티 최대 인원 (아군, 적군 공통)

#define CLASS_TOTAL 4

#define CHARACTER_LVL_MAX 10

#define NAME_LIMIT 12

#define COMMON_MAXHP_ORIGIN 50
#define COMMON_ATK_ORIGIN 25
#define COMMON_DEF_ORIGIN 10
#define COMMON_SPD_ORIGIN 10

#define COMMON_MAXHP_PER_LVL 10
#define COMMON_ATK_PER_LVL 10
#define COMMON_DEF_PER_LVL 10
#define COMMON_SPD_PER_LVL 10

enum class Class {
  COMMON,
  WARRIOR,
  ARCHOR,
  THIEF,
};

class Character {
  static int num_of_character;

  std::string name;
  Class class_of_character;

  int max_hp;
  double hp;
  int atk;
  int def;
  int spd;

  int lvl;

  bool is_dead;

 public:
  Character();
  Character(std::string _name, int _lvl);

  std::string GetClass() const;

  virtual void PrintStatus();

  virtual ~Character();
};
#pragma once
#include "Character.h"
#include "Skill.h"

class Hero : public Character {
  double exp;
  int max_exp;

  static int gold;
  Skill* skills;

 public:
  Hero();
  Hero(std::string _name, int _lvl);
  Hero(const Hero& other);

  //Gold
  int GetGold() const;
  static void SetGold(int _gold);
  static void AddGold(int _gold);

  //Get
  int GetMaxExpForCurrentLvl() const;
  void GiveExp(int _exp);

  virtual void PrintStatus();
  void PrintExp();

  ~Hero();
};
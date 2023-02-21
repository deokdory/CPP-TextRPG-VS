#pragma once
#include "Character.h"
#include "Skill.h"
  //int gold = 0;

class Hero : public Character {

  double exp;
  int max_exp;

  Skill* skills;

 public:
  Hero();
  Hero(std::string _name, int _lvl);
  Hero(const Hero& other);

  //Gold

  //Get
  int GetMaxExpForCurrentLvl() const;

  void GiveExp(int _exp);


  virtual void PrintStatus();
  void PrintExp();

  ~Hero();
};
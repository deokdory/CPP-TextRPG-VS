#pragma once
#include "Character.h"

class Hero : public Character {
  double exp;
  int max_exp;

  static int gold;

 public:
  Hero();
  Hero(std::string _name, int _lvl);
  Hero(const Hero& other);

  int GetMaxExpForCurrentLvl() const;

  virtual void PrintStatus();

  ~Hero();
};
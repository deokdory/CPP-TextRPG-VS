#pragma once
#include "Character.h"

class Skill : public Character {
 protected:
  int cooldown;
  int cooldown_remain;

 public:
  Skill();
  // Get
  int GetCoolDown() const;
  int GetCoolDownRemain() const;

  // Set
  void SetCoolDown(int _cooldown);

  // Virtual
  virtual void Use();
  bool IsAvailable();
};

#pragma once
//#include <string>
enum class SkillType {
  ATTACK,
  DEBUFF,
  HEAL,
  BUFF,
};

class Skill {
 protected:
  int cooldown;
  int cooldown_remain;
  SkillType skill_type;

 public:
  Skill();
  Skill(int _cooldown, int _cooldown_remain, SkillType _type);
  Skill(const Skill& other);
  // Get
  int GetCoolDown() const;
  int GetCoolDownRemain() const;

  // Set
  void SetCoolDown(int _cooldown);

  // Virtual
  virtual void Use();
  bool IsAvailable();
};

class StrongAttack : public Skill {
private:
	Character Owner;
public:
	StrongAttack(Character _Owner);

	virtual void Use(Character _Target);
};
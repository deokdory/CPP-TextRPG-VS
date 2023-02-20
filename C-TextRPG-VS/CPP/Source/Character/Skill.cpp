#include "pch.h"
#include "Skill.h"

//스킬 클래스
Skill::Skill() : cooldown(0) { name = "NULL"; }

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }

void Skill::Use() { std::cout << "NULL SKILL" << std::endl; }
bool Skill::IsAvailable() {
	if (!GetCoolDownRemain()) {
		return true;
	}
	else {
		std::cout << "아직 사용할 수 없습니다" << std::endl;
		return false;
	}
}

//세게 때리기
StrongAttack::StrongAttack(Character _Owner) : Owner(_Owner) {
    name = "세게 때리기";
}

void StrongAttack::Use(Character _Target) {
    if (IsAvailable()) {
        std::cout << Owner.GetName() << "(이)가 " << GetName() << "을 사용했다!"
            << std::endl;
        Owner.SetAtk(Owner.GetAtk() * 1.3);
        Owner.Attack(_Target);
    }
}
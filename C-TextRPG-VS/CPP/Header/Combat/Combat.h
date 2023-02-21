#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Skill.h"
#include "GameManager.h" // Quest, Gold ��

enum class Place {
	FOREST, CAVE, MOUNTAIN
};

enum ActionInCombat {
	ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY
};

	void Combat(Place _place); // ���� ����

	int GetEnemiesPersonnel(Place _place); // �� ��ü �ο� �� ���
  int GetEnemyLvl(Place _place); // �� ���� ���
  std::string GetEnemyName(Place _place);
	void Action(Character _character); // ���� �� �ൿ
	void RunAway(Character _character); // ���� spd ���ؼ� Ȯ�� ���� �� ����

#pragma once

#include "Hero.h"
#include "Enemy.h"
//#include "Quest.h"

enum class Place {
	FOREST, CAVE, MOUNTAIN
};

enum ActionInCombat {
	ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY
};

class Combat
{
	int allies_alive, enemy_alive;
	int total_reward_gold;

public:
	Combat(Place _place); // ���� ����
 ~Combat(); // delete enemy, �¸����� �� ������ ����

 void SetEnemy(Place _place); // ��ҿ� ���� lvl �� name �����ؼ� Enemy ����, total_reward_gold �Ҵ�
 void Action(Character _character); // ���� �� �ൿ
 void RunAway(Character _character); // ���� spd ���ؼ� Ȯ�� ���� �� ����
};
#pragma once
#include "Character.h"
#include "Common.h"

enum class Place { FOREST, CAVE, MOUNTAIN };

enum ActionInCombat { ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY };

void Combat(Hero** Player, Place _place);  // ���� ����

int GetEnemiesPersonnel(Place _place);  // �� ��ü �ο� �� ���
int GetEnemyLvl(Place _place);          // �� ���� ���
std::string GetEnemyName(Place _place);
void Action(Character _character);  // ���� �� �ൿ
void RunAway(Character _character);  // ���� spd ���ؼ� Ȯ�� ���� �� ����

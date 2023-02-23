#pragma once
#include "Character.h"
#include "System.h"
#include "GameManager.h"

enum class Place { FOREST, CAVE, MOUNTAIN };

enum ActionInCombat { ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY };

void Combat(GameManager& Game, Hero** Player, Place _place);  // ���� ����

//�� ����
int GetEnemiesPersonnel(Place _place);  // �� ��ü �ο� �� ���
int GetEnemyLvl(Place _place);          // �� ���� ���
std::string GetEnemyName(Place _place);

void RunAway(Character& _character);  // ���� spd ���ؼ� Ȯ�� ���� �� ����

Character* SelectTarget(Enemy*, int personnel);
Character* SelectTarget(Hero**, int personnel);
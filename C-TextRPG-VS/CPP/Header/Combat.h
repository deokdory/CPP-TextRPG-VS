#pragma once
#include "Character.h"
#include "Item.h"
#include "System.h"
#include "GameManager.h"

enum ActionInCombat { COMBAT_ATTACK = 1, COMBAT_USE_SKILL, COMBAT_USE_ITEM, COMBAT_RUNAWAY };

void Combat(GameManager& Game, Hero** Player, Place _place);  // ���� ����

//�� ����
int GetEnemiesPersonnel(Place _place);  // �� ��ü �ο� �� ���
int GetEnemyLvl(Place _place);          // �� ���� ���
int GetEnemyIndex(Place _place);

void RunAway(Character& _character);  // ���� spd ���ؼ� Ȯ�� ���� �� ����
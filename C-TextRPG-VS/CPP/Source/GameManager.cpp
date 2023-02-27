#include "pch.h"
#include "GameManager.h"

int GameManager::gold = 0;

const int GameManager::GetGold() { return gold; }

void GameManager::SetGold(int _gold) { gold = _gold; }

void GameManager::AddGold(int _gold) { gold += _gold; }

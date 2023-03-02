#include "pch.h"
#include "GameManager.h"

int GameManager::gold = 0;
bool GameManager::game_ended = false;

const int GameManager::GetGold() { return gold; }

void GameManager::SetGold(int _gold) { gold = _gold; }

void GameManager::AddGold(int _gold) { gold += _gold; }

void GameManager::SetGameEnded(bool _game_ended) { game_ended = _game_ended; }
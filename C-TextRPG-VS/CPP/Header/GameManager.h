#pragma once

enum class Place { TOWN, WORLD_MAP, FOREST, CAVE, MOUNTAIN };

class GameManager {
  static int gold;
  
  static bool game_ended;
 public:
  static const int GetGold();
  static void SetGold(int _gold);
  static void AddGold(int _gold);

  static bool IsGameEnded() { return game_ended; }
  static void SetGameEnded(bool _game_ended);
};


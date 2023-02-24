#pragma once

class GameManager {
  int gold;
  int top_lvl_of_player;

  //Quest* ProgressQuest;

 public:
  int GetGold();
  void SetGold(int _gold);
  void AddGold(int _gold);

  
};
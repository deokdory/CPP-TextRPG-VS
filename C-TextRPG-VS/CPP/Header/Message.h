#pragma once
#define SYSTEM_MESSAGE_DELAY Sleep(1500)
class Message {
 public:
  void SystemMessage(std::string _message, int _delay = 1500);
};
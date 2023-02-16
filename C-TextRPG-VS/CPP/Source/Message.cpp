#include "pch.h"
#include "Message.h"

void Message::SystemMessage(std::string _message, int _delay) {
  std::cout << _message << std::endl;
  Sleep(_delay);
}

#include "pch.h"
#include "Message.h"
//#include <string>

void Message::SystemMessage(std::string _message, int _delay) {
  std::cout << _message << std::endl;
  delay(_delay);
}

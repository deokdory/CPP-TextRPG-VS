#include "pch.h"
#include "System.h"

void gotoxy(short x, short y) {
  COORD Cur;
  Cur.X = x;
  Cur.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void gotox(short x) {
  CONSOLE_SCREEN_BUFFER_INFO temp;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
  COORD Cur;
  Cur.X = x;
  Cur.Y = temp.dwCursorPosition.Y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void gotoy(short y) {
  CONSOLE_SCREEN_BUFFER_INFO temp;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
  COORD Cur;
  Cur.X = temp.dwCursorPosition.X;
  Cur.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void TextColor(int foreground, int background) {
  int color = foreground + background * 16;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

double RealRandom() {
  double random[10] = {};
  for (int i = 0; i < 10; i++) {
    random[i] = random();
  }
  return random[rand() % 10];
}
void ClearFromY(short y, int lines) {
  gotoxy(0, y);
  for (int i = 0; i < lines; i++) {
    std::cout << "                                                           "
                 "                                         "
              << std::endl;
  }
  gotoy(y);
}
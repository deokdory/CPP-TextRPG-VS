#include "pch.h"
#include "Common.h"

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
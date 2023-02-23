#pragma once

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHT_GRAY    7
#define DARK_GRAY     8
#define LIGHT_BLUE    9 
#define LIGHT_BREEN   10
#define LIGHT_CYAN    11
#define LIGHT_RED     12
#define LIGHT_MAGENTA 13
#define YELLOW        14
#define WHITE         15

void gotoxy(short x, short y);
void gotox(short x);
void gotoy(short y);

void TextColor(int foreground = LIGHT_GRAY, int background = BLACK);

double RealRandom();
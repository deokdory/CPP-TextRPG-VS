#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <cstdlib>

#undef random
#define random() ((double)rand() / RAND_MAX)

#define RESET_FORMAT std::cout.copyfmt(std::ios(NULL))

#define endll std::endl << std::endl
#define ENDL std::cout << std::endl

#define SYSTEM_MESSAGE_DELAY Sleep(1500)

//void delay(clock_t n) {
//  clock_t start = clock();
//  while (clock() - start < n);
//}
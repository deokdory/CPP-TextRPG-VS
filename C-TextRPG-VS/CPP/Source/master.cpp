#include "pch.h"
#include "master.h"
 
int main() {
  Character Character1;
  Character1.PrintStatus();

  Character Test("AAAAAAAAAAAA", 5);
  Test.PrintStatus();

  Character* Hero1 = new Hero;
  Hero1->PrintStatus();
  ENDL;

  delete Hero1;

  return 0;
}
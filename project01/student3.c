#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(void) {
  assert(pell(0) == 0);
  assert(pell(1) == 1);
  assert(pell(2) == 2);
  assert(pell(3) == 5);
  assert(pell(5) == 29);
  assert(pell(-1) == -1);
  assert(pell(-3) == -1);

  printf("\nThis test has passed!\n");

  return 0;
}

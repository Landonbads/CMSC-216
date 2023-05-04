#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(void) {
  assert(compare_rectangles(200,200,216,216) == -1);
  assert(compare_rectangles(216,216,200,200) == 1);
  assert(compare_rectangles(216,216,216,216) == 0);
  assert(compare_rectangles(-216,216,216,216) == -2);

  printf("\nThis test has passed!\n");

  return 0;
}

#include "functions.h"

/* Name: Landon Badstibner
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 * Project 01 - 3 functions using basic C features
 * I pledge on my honor that I have not given or received any unauthorized assistance on this assignment
 */


/* Returns a value indicating how two rectangles area's compare
 * Returns 1 if area of rectangle 1 is larger than rectangle 2, -1 if smaller, and 0 if the same
 */
short compare_rectangles(int l1, int w1, int l2, int w2) {
  int rect1_area = l1 * w1;
  int rect2_area = l2 * w2;
  if ( l1 < 0 || w1 < 0 || l2 < 0 || w2 < 0 )
    return -2;
    else if ( rect1_area < rect2_area ) 
      return -1;
    else if ( rect1_area > rect2_area ) 
      return 1;
    else
      return 0;
}

/* Returns the ith common positive factor between two numbers, returns -1 if no common factor exists
 *
 */
int ith_factor(int a, int b, int i) {
  int counter = 0;
  int z;
  if( a < 0 )
    a = a * -1;
  if( b < 0 )
    b = b * -1;

  for ( z = 1; z <= a && z <= b; z++ ) {
    if ( a % z == 0 && b % z == 0 ) {
      counter++;
    }
    if ( counter == i )
      return z;
  }
  return -1;
}

/* Computes and returns the pell number of entry n
 */
long pell(short n) {
  int i;
  long previous_num1 = 0;
  long previous_num2 = 1;
  long previous_placeholder;
  if( n == 0 )
    return previous_num1;
  if ( n == 1 ) 
    return previous_num2;
  if( n < 0 ) 
    return -1;

  for ( i = 2; i < n; i++ ) {
    previous_placeholder = previous_num2;
    previous_num2 = (2 * previous_num2) + previous_num1;
    previous_num1 = previous_placeholder;
  }
  return (2 * previous_num2) + previous_num1;
}

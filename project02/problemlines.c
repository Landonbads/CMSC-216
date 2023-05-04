/* Name: Landon Badstibner
 * Date: 02/16/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 02 - A program to read the a file in lengthwarning.c output format
 * and print the line numbers of the lines that exceed 80 characters
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#include <stdio.h>

/* function prototype(s) */
int reset_array(char[], int);


/**
 * Main function to execute code
 * @return 0 for success or -1 for failure
 */
int main(void) {
  /* declare/initialize variables */
  int initial_var = 1;
  int size = 0;
  char chars[999];
  int line_num = 0;
  int lines_printed = 0;

  /* loop until EOF */
  while (!feof(stdin)) {
    /* scan character and add it to array */
    scanf("%c", &chars[size]);
    /* increment size of line by 1 */
    size++;

    /* checks whether or not to read first char or skip the line */
    if (initial_var == 1) {
      /* checks if the intial character is an asterix */
      if (chars[0] == '*') {
	/* scans the next decimal (in this case, line number) */
	scanf("%d", &line_num);

	/* checks if the # of lines exceeding 80 that were printed
	   is more than 0. This is to ensure there are no white spaces
	   before and after the first and last numbers. */
	if (lines_printed > 0) {
	  /* lines_printed > 0, this is not the first # printed,
	     so print a white space before the to be printed num. */
	  printf(" %d", line_num);
	}
	else {
	  /* lines_printed == 0, this is the first # to be printed,
	     so do not print a white space before the num. */
	  printf("%d", line_num);
	}
	lines_printed++;
      }

      /* set initial_var to 0 (false) to skip rest of line */
      initial_var = 0;
      /* set size to output of reset_array function, which is 0. */
      size = reset_array(chars, size);
    }

    /* checks if scanned char is a newline character. If it is, reset array
       and set size of line to 0 to prepare for next line. Also reset
       initial_var to 1 (true). */
    if (chars[size - 1] == '\n') {
      size = reset_array(chars, size);
      initial_var = 1;
    }
  }
  /* print a newline once EOF has been reached. */
  printf("%c", '\n');

  return 0;
}


/**
 * Resets the char array
 * @param char array[]
 * @param int size of array
 */
int reset_array(char arr[], int size) {
  int index;

  for (index = 0; index < size; index++) {
    arr[index] = '\0';
  }

  return 0;
}

/* Name: Landon Badstibner
 * Date: 02/16/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 02 - A program to check for lines in an input that are more
 * than 80 characters. If a line exceeds 80 characters, the code will
 * output the line number and identify the exceeding chars.
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#include <stdio.h>

/* function prototypes */
void reset_array(char[], int);
void exceeds_eighty(int, int);
int print_line(int, int, int, int, char[]);

/**
 * Main function
 * @return 0 for success or -1 for failure
 */
int main(void)
{
  /* initialize variables */
  int size = 0;
  char line[1000];
  int length = 0;
  int line_num = 0;
  int exceeds = 0;

  /* loop until EOF */
  while ( !feof(stdin) ) {
    /* scan character and add it to array */
    scanf("%c", &line[size]);

    /* if the character is a tab, then increase length by
       number of chars before tab stop */
    if ( line[size] == '\t' ) {
      length += 8 - (length % 8);
    }
    /* increase length by one if the character is not a newline character */
    else if ( line[size] != '\n') {
      length++;
    }
    /* increment size of line by 1 */
    size++;

    /* if character is a new line character increase line number count*/
    if ( line[size - 1] == '\n' ) {
      /* increase line number by 1 */
      line_num++;

      /* print first line of output */
      exceeds = print_line(length, size, exceeds, line_num, line);

      /* check whether or not to print second line */
      exceeds_eighty(exceeds, length);

      /* set variables to 0 and reset the array to null values to prepare for
	 the next line */
      size = 0;
      length = 0;
      exceeds = 0;
      reset_array(line, size);
    }
  }
  return 0;
}


/**
 * print_line function to print out first line of output
 * @param length - length of line
 * @param size - size of line
 * @param exceeds - 1 if line exceeds length 80, 0 if line doesn't
 * @param line_num - the line number
 * @param arr - array of characters
 * @return exceeds - exceeds value to pass back to main function
 */
int print_line(int length, int size, int exceeds, int line_num, char arr[])
{
  /* declare loop variable i */
  int i;

  /* if length of the line is more than 80, set exceeds var to true (1)
     and print asterix followed by the number of the line */
  if (length > 80) {
    exceeds = 1;
    printf("*%5d: ", line_num);
  }
  /* if length is not more than 80, print space followed by line number */
  else {
    printf(" %5d: ", line_num);
  }

  /* loop through size of line and print every character */
  for (i = 0; i < size; i++) {
    printf("%c", arr[i]);
  }
  return exceeds;
}


/**
 * Resets the char array
 * @param char array[]
 * @param int size of array
 */
void reset_array(char arr[], int limit)
{
  int index;
  for (index = 0; index < limit; index++) {
      arr[index] = '\0';
    }
}


/**
 * check if line exceeds 80 and if so, print 88 spaces under first line
 * followed by carets under the characters that exceeded the length of 80.
 * @param int exceed value
 * @param int length of line
 */
void exceeds_eighty(int exceed, int length)
{
  int i;

  /* checks if line exceeds length of 80 */
  if (exceed == 1) {
    /* iterates through the length of line plus 8 */
    for (i = 0; i < length + 8; i++) {
      /* print space under every char that does not exceed 80 */
      if (i < 88) {
        printf(" ");
      }
      /* print a caret under every char that exceeds 80 */
      else {
        printf("^");
      }
    }
    printf("\n");
  }
}

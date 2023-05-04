/* Name: Landon Badstibner
 * Date: 04/24/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 09 - A project to simulate the UNIX xargs utility function. It takes
 * allows programs that take command-line arguments only to work with standard
 * input.
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include "safe-fork.h"
#include "split.h"

int main(int argc, char **argv)
{
	/* set needed variables */
	char line[10000];
	int n_option = 0, i = 0, status, num_args = 0;
	char *target_program;
	pid_t pid;
	char **newarg_list = NULL;
	char **split_list = NULL;

	/* if first argument is -n, set n_option to 0 */
	if (argc > 1)
	{
		/* check if -n is the first argument */
		if (strcmp(argv[1], "-n") == 0)
			n_option = 1;

		/* if -n is the first command-line argument, execute
		 the following block of code*/
		if (n_option)
		{
			/* iterate through the standard input. Program will
			exit with 0 exit status if no standard input. */
			while (fgets(line, 10000, stdin) != NULL)
			{
				/* if statement to check if # of command-line
				args more than 2 to ensure a target program
				name was passed in. */
				if (argc > 2)
				{
					/* print the commands that would be
					executed if -n was not given. */
					for (i = 2; i < argc; i++)
						printf("%s ", argv[i]);

					printf("%s", line);
				}
			}
		}
		/* if the first argument is not -n */
		else
		{
			/* set target program to second
			command-line argument */
			target_program = argv[1];

			/* loop through standard input */
			while (fgets(line, 10000, stdin) != NULL)
			{
				/* split stdinput */
				split_list = split(line);

				/* count number of elements in split list array
				 excluding null element */
				for (i = 0; split_list[i] != NULL; i++)
				{
					num_args++;
				}

				/* allocate memory for new array of strings
				with size allowingnumber of command-line
				arguments and stdin arguments */
				newarg_list = malloc(((argc - 1) + (num_args + 1)) *
									 sizeof(char *));

				/* check if memory allocation was
				successful */
				if (newarg_list == NULL)
				{
					perror("memory allocation failure");
					exit(0);
				}

				/* loop through command-line arguments and
				allocate memory for each string.
				Subsequently copy elements over */
				for (i = 1; i < argc; i++)
				{
					newarg_list[i - 1] = malloc(strlen(argv[i]) + 1);

					/* check if memory allocation was
					 successful */
					if (newarg_list[i - 1] == NULL)
					{
						perror("memory allocation failure");
						exit(0);
					}

					strcpy(newarg_list[i - 1], argv[i]);
				}

				/* loop through stdin and allocate memory
				for each string. Subsequently copy elements
				 over to new array */
				for (i = 0; split_list[i] != NULL; i++)
				{
					newarg_list[i + (argc - 1)] =
						malloc(strlen(split_list[i]) + 1);

					/* check if memory allocation was
					 successful */
					if (newarg_list[i + (argc - 1)] == NULL)
					{
						perror("memory allocation failure");
						exit(0);
					}

					strcpy(newarg_list[i + (argc - 1)], split_list[i]);
				}

				/* set last element to NULL */
				newarg_list[i + (argc - 1)] = NULL;

				/* fork process */
				pid = safe_fork();

				/* execute if parent process */
				if (pid > 0)
				{
					/* if parent, wait for child and
					store status */
					wait(&status);

					/* if exit status not 0 then exit the
					program with same exit status
					as the child */
					if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
						exit(WEXITSTATUS(status));
				}
				/* execute if child process */
				else if (pid == 0)
				{
					/* if child process then execute
					desired command */
					execvp(target_program, newarg_list);

					/* exit with status 255 if
					exec call fails */
					exit(255);
				}

				/* freeeee every string in the dynamically
				allocated split array */
				for (i = 0; split_list[i] != NULL; i++)
					free(split_list[i]);
				/* free the split array itself */
				free(split_list);

				/* freeeee every string in the dynamically
				allocated newarg array */
				for (i = 0; newarg_list[i] != NULL; i++)
					free(newarg_list[i]);
				/* free the newarg array itself */
				free(newarg_list);
			}
		}
		/* exit with status 0 */
		exit(0);
	}
	return 0;
}
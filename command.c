#include "shell.h"

/**
 * split_command - Split a command line into arguments
 * @input: The input command line
 * @args: An array to store the arguments
 * @arg_count: A pointer to store the argument count
 */
void split_command(char *input, char *args[], int *arg_count)
{
	char *token = strtok(input, " ");
	*arg_count = 0;

	while (token != NULL)
	{
		args[(*arg_count)++] = token;
		token = strtok(NULL, " ");
	}

	args[*arg_count] = NULL;
}

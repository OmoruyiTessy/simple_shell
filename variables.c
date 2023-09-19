#include "shell.h"

/**
 * replace_variables - Replace variables in a command line
 * This function replaces variables in a command line
 * @command: The command line to process
 *
 * Return: A pointer to the new command line
 */
char *replace_variables(char *command)
{
	char *new_command = malloc(MAX_INPUT_SIZE);
	char *source = command;
	char *destination = new_command;

	if (new_command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (*source)
	{
		if (source[0] == '$' && source[1] == '$')
		{
			snprintf(destination, 10, "%d", getpid());
			destination += strlen(destination);
			source += 2;
		}
		else if (source[0] == '$' && source[1] == '?')
		{
			snprintf(destination, 10, "%d", last_exit_status);
			destination += strlen(destination);
			source += 2;
		}
		else
		{
			*destination = *source;
			destination++;
			source++;
		}
	}
	*destination = '\0';

	return (new_command);
}

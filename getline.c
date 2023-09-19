#include "shell.h"
/**
 * custom_getline - Custom implementation of getline
 *
 * This function will implement the getline
 * Return: A pointer to the line read or NULL on failure.
 */
char *custom_getline(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		perror("getline");
		free(line);
		exit(EXIT_FAILURE);
	}
	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}

	return (line);
}

#include "shell.h"

/**
 * processFileCommands - Process commands from a file
 * @filename: The name of the file containing commands
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int processFileCommands(const char *filename)
{
	char *input = NULL;
	size_t input_size = 0;
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}

	while (getline(&input, &input_size, file) != -1)
	{
		if (input[strlen(input) - 1] == '\n')
		{
			input[strlen(input) - 1] = '\0';
		}

		char *command_with_variables = replace_variables(input);

		execute_command(command_with_variables);

		free(command_with_variables);
	}

	fclose(file);

	free(input);

	return (EXIT_SUCCESS);
}

/**
 * processInteractiveShell - Process interactive shell input
 *
 */
void processInteractiveShell(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_bytes;

	while (1)
	{
		printf("$ ");

		read_bytes = getline(&input, &input_size, stdin);

		if (read_bytes == -1)
		{
			printf("\n");
			break;
		}

		if (input[read_bytes - 1] == '\n')
		{
			input[read_bytes - 1] = '\0';
		}

		if (strncmp(input, "alias", 5) == 0)
		{
			handleAliasCommand(input);
		}
		else
		{
			executeInputCommand(input);
		}
	}

	free(input);
}

/**
 * main - The main function of the shell
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		return (processFileCommands(argv[1]));
	}
	else if (argc == 1)
	{
		processInteractiveShell();
	}
	else
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	cleanupAliases();
	return (EXIT_SUCCESS);
}

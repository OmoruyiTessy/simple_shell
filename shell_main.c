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
	char *command_with_variables = NULL;

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

		if (command_with_variables != NULL)
		{
			free(command_with_variables);
			command_with_variables = NULL;
		}

		command_with_variables = replace_variables(input);

		execute_command(command_with_variables);

		free(command_with_variables);
		command_with_variables = NULL;
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
 * cleanupAliases - Cleanup the alias list
 *
 * This function frees the memory associated with the alias list.
 */
void cleanupAliases(void)
{
	struct Alias *current = alias_list;
	struct Alias *temp = current;

	while (current != NULL)
	{
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	alias_list = NULL;
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
	int result;

	if (argc == 2)
	{
		result = processFileCommands(argv[1]);
	}
	else if (argc == 1)
	{
		processInteractiveShell();
		result = EXIT_SUCCESS;
	}
	else
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	cleanupAliases();
	return (result);
}

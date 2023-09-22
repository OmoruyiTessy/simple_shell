#include "shell.h"

/**
 * processFileCommands - Process commands from a file
 *
 * This function reads and processes commands from a file with
 * the given filename.
 *
 * @filename: The name of the file containing commands
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int processFileCommands(const char *filename)
{
	int last_exit_status = 0;
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

		command_with_variables = replace_variables(input, &last_exit_status);

		execute_command(command_with_variables, &last_exit_status);

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
 * This function process interactive shell input, allowing the
 * user to enter commands
 *
 * @alias_list: A pointer to the alias list.
 * @last_exit_status: pointer to the last exit status variable
 */
void processInteractiveShell(struct Alias **alias_list, int *last_exit_status)
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
			handleAliasCommand(input, alias_list, last_exit_status);
		}
		else
		{
			executeInputCommand(input, alias_list, last_exit_status);
		}
	}

	free(input);
}

/**
 * cleanupAliases - Cleanup the alias list
 *
 * This function frees the memory associated with the alias list.
 *
 * @alias_list: A pointer to the alias list.
 */
void cleanupAliases(struct Alias **alias_list)
{
	struct Alias *current = *alias_list;
	struct Alias *temp = current;

	while (current != NULL)
	{
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	*alias_list = NULL;
}

/**
 * main - The main function of the shell
 *
 * This is the main function of the shell program
 *
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	int result;
	struct Alias *alias_list = NULL;
	int last_exit_status = 0;

	if (argc == 2)
	{
		result = processFileCommands(argv[1], &alias_list,
				&last_exit_status);
	}
	else if (argc == 1)
	{
		processInteractiveShell(&alias_list, &last_exit_status);
		result = EXIT_SUCCESS;
	}
	else
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	cleanupAliases(&alias_list);
	return (result);
}

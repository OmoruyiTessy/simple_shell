#include "shell.h"
/**
 * print_aliases - Print all aliases
 */
void print_aliases(void)
{
	struct Alias *current = alias_list;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

/**
 * print_specific_aliases - Print specific aliases
 * @names: An array of alias names
 * @name_count: The number of alias names in the array
 */
void print_specific_aliases(char *names[], int name_count)
{
	struct Alias *current = alias_list;
	int i;

	while (current != NULL)
	{
		for (i = 0; i < name_count; i++)
		{
			if (strcmp(current->name, names[i]) == 0)
			{
				printf("%s='%s'\n", current->name, current->value);
				break;
			}
		}
		current = current->next;
	}
}

/**
 * add_alias - Add or update an alias
 * @name: The alias name
 * @value: The alias value
 */
void add_alias(char *name, char *value)
{
	struct Alias *current = alias_list;
	 struct Alias *new_alias = malloc(sizeof(struct Alias));

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return;
		}
		current = current->next;
	}
	if (new_alias == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = alias_list;
	alias_list = new_alias;
}

/**
 * handleAliasCommand - This Handle the "alias" command
 * @input: The input command line
 *
 * This function is responsible for processing and adding aliases based on the
 * input command line.
 */
void handleAliasCommand(char *input)
{
	char *name = strtok(input + 6, "=");
	char *value = strtok(NULL, "=");

	if (name != NULL && value != NULL)
	{
		add_alias(name, value);
	}
	else
	{
		printf("Usage: alias name=value\n");
	}
}

/**
 * executeInputCommand - Execute a regular input command
 * @input: The input command line
 *
 * This function is responsible for executing regular input
 * commands (not aliases).
 */
void executeInputCommand(char *input)
{
	char *command_with_variables = replace_variables(input);

	execute_command(command_with_variables);
	free(command_with_variables);
}

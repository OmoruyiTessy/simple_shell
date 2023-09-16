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

	while (current != NULL)
	{
		for (int i = 0; i < name_count; i++)
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

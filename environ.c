#include "shell.h"

/**
 * shell_print_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int shell_print_env(info_t *info)
{
	print_list_string(info->env);
	return (0);
}

/**
 * shell_get_env - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the environment variable or NULL if not found.
 */
char *shell_get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = custom_starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_set_env - Initializes a new environment variable
 *                 or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: it always 0
 */
int shell_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		shell_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (shell_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_unset_env - Removes an environment variable
 * @info: Structure containing potential arguments.
 * Return: it will always be 0
 */
int shell_unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		shell_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		shell_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * shell_populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int shell_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

#include "shell.h"

/**
 * shell_history - This displays the history list, one command per line,
 * preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: it will always 0
 */
int shell_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_shell_alias - unsets a shell alias
 * @info: Parameter struct.
 * @alias_str: The alias string to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_shell_alias(info_t *info, char *alias_str)
{
	char *equal_sign, temp_char;
	int ret;

	equal_sign = custom_strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	temp_char = *equal_sign;
	*equal_sign = '\0';

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, find_node_with_prefix(info->alias,
				alias_str, -1)));

	*equal_sign = temp_char;

	return (ret);
}

/**
 * set_shell_alias - sets a shell alias
 * @info: Parameter struct.
 * @alias_str: The alias string to set.
 *
 * Return: 0 on success, 1 on error.
 */
int set_shell_alias(info_t *info, char *alias_str)
{
	char *equal_sign;

	equal_sign = custom_strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (unset_shell_alias(info, alias_str));

	unset_shell_alias(info, alias_str);

	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_shell_alias - prints a shell alias string
 * @node: The alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_shell_alias(list_t *node)
{
	char *equal_sign, *alias;

	if (node)
	{
		equal_sign = custom_strchr(node->str, '=');
		alias = node->str;

		while (alias <= equal_sign)
			custom_putchar(*alias++);

		custom_putchar('\'');
		custom_puts(equal_sign + 1);
		custom_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * shell_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *
 * Return: it will always 0
 */
int shell_alias(info_t *info)
{
	int i;
	char *equal_sign, *alias_str;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_shell_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = custom_strchr(info->argv[i], '=');
		alias_str = info->argv[i];

		if (equal_sign)
			set_shell_alias(info, alias_str);
		else
			print_shell_alias(find_node_with_prefix(info->alias,
						alias_str, '='));

	}

	return (0);
}

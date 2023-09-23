#include "shell.h"

/**
 * list_length - this determines the length of a linked list
 * @head: pointer to the first node of the list
 *
 * Return: size of the list
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t list_size = list_length(head);
	size_t i, j;
	char **strs;
	char *str;

	if (!head || list_size == 0)
		return (NULL);

	strs = malloc(sizeof(char *) * (list_size + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = custom_strdup(node->str);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		custom_puts(int_to_str(head->num, 10, 0));
		custom_putchar(':');
		custom_putchar(' ');
		custom_puts(head->str ? head->str : "(nil)");
		custom_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * find_node_with_prefix - returns the node whose string starts with a prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char c)
{
	while (head)
	{
		if (custom_starts_with(head->str, prefix) &&
				(c == -1 || head->str[custom_strlen(prefix)] == c))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

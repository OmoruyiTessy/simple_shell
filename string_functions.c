#include "shell.h"
/**
 * custom_strcpy - This copies a string from source to destination.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: pointer to the destination buffer.
 */
char *custom_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * custom_strdup - Duplicates a string for the simple shell project.
 * @str: The string to duplicate.
 *
 * Return: pointer to the duplicated string, or NULL on failure.
 */
char *custom_strdup(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return (NULL);
	for (length++; length--;)
		duplicate[length] = *--str;
	return (duplicate);
}
/**
 * custom_puts - Prints a string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void custom_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		custom_putchar(str[i]);
		i++;
	}
}
/**
 * custom_putchar - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

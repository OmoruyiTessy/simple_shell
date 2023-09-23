#include "shell.h"
/**
 * custom_strncpy - copies a string up to a specified length
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the maximum number of characters to copy
 * Return: a pointer to the destination string
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *d = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (d);
}
/**
 * custom_strncat - concatenates two strings up to a specified length
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of characters to concatenate
 * Return: a pointer to the destination string
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
/**
 * custom_strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if not found
 */
char *custom_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

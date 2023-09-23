#include "shell.h"
/**
 * custom_strncpy - copies a string up to a specified length
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the maximum number of characters to copy
 * Return: a pointer to the destination string
 */
char *custom_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;
	char *result = dest;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (result);
}
/**
 * custom_strncat - concatenates two strings up to a specified length
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of characters to concatenate
 * Return: a pointer to the destination string
 */
char *custom_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}
/**
 * custom_strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if not found
 */
char *custom_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

#include "shell.h"
/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: a pointer to the info struct
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: a string containing delimiters
 *
 * Return: 1 if the character is a delimiter, 0 if otherwise
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}
/**
 * is_alphabetic - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * string_to_integer - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the converted integer, or 0 if no numbers in the string
 */
int string_to_integer(char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;
	int flag = 0;

	if (s == NULL)
		return (0);

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;

		i++;
	}
	return (sign * result);
}

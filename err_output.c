#include "shell.h"
/**
 * str_to_int - This converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * print_custom_error - prints a custom error message
 * @info: the parameter & return info struct
 * @error_str: string containing the specified error type
 */
void print_custom_error(info_t *info, char *error_str)
{
	shell_puts(info->fname);
	shell_puts(": ");
	shell_print_d(info->line_count, STDERR_FILENO);
	shell_puts(": ");
	shell_puts(info->argv[0]);
	shell_puts(": ");
	shell_puts(error_str);
}
/**
 * shell_print_d - prints a decimal (integer) number (base 10)
 * @input: the input number
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int shell_print_d(int input, int fd)
{
	int (*putchar_func)(char) = shell_putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		putchar_func = shell_putchar;
	if (input < 0)
	{
		abs_value = -input;
		putchar_func('-');
		count++;
	}
	else
		abs_value = input;
	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			putchar_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	putchar_func('0' + current);
	count++;
	return (count);
}
/**
 * int_to_str - converts an integer to a string
 * @num: the integer to convert
 * @base: the base of the conversion
 * @flags: argument flags
 *
 * Return: string representation of the integer
 */
char *int_to_str(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comment - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

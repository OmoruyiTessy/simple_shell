#include "shell.h"

/**
 * main - The main function of the shell
 *
 * This is the main function of the shell program
 *
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char **argv)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				shell_puts(argv[0]);
				shell_puts(": 0: Can't open ");
				shell_puts(argv[1]);
				shell_putchar('\n');
				shell_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = fd;
	}
	shell_populate_env_list(&info);

	read_history(&info);
	shell_lp(&info, argv);

	return (EXIT_SUCCESS);
}

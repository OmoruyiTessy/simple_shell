#include "shell.h"
/**
 * shell_exit - This exits the shell
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status, 0 if info->argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exit_status = 0;

	if (info->argv[1])
	{
		exit_status = string_to_integer(info->argv[1]);
		if (exit_status < 0)
		{
			info->status = 2;
			print_custom_error(info, "Illegal number: ");
			shell_puts(info->argv[1]);
			shell_putchar('\n');
			return (1);
		}
		info->err_num = exit_status;
	}
	else
	{
		info->err_num = -1;
	}
	return (-2);
}
/**
 * shell_cd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_cd(info_t *info)
{
	char *dir, *s, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = shell_get_env(info, "HOME=");
		if (!dir)
			dir = shell_get_env(info, "PWD=");
		chdir_ret = chdir(dir ? dir : "/");
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		dir = shell_get_env(info, "OLDPWD=");
		if (!dir)
		{
			custom_puts(s);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(dir);
		custom_putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}
	if (chdir_ret == -1)
	{
		print_custom_error(info, "can't cd to ");
		shell_puts(info->argv[1]);
		shell_putchar('\n');
	}
	else
	{
		shell_setenv(info, "OLDPWD", shell_get_env(info, "PWD="));
		shell_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * shell_help - displays help information
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_help(info_t *info)
{
	char **arg_array = info->argv;

	custom_puts("Help information for the shell. Function not yet implemented.\n");
	if (arg_array)
		custom_puts(*arg_array);
	return (0);
}

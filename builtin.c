#include "shell.h"

/**
 * shell_exit - exits the shell
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status, 0 if info->argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exit_status = 0;

	if (info->argv[1])
	{
		exit_status = _atoi(info->argv[1]);
		if (exit_status < 0)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
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
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");

		chdir_ret = chdir(dir ? dir : "/");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}

		_puts(dir);
		_putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
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

	_puts("Help information for the shell. Function not yet implemented.\n");
	if (arg_array)
		_puts(*arg_array); /* Temporary unused variable workaround */

	return (0);
}

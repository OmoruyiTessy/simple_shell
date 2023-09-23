#include "shell.h"

/**
 * shell_lp - Main shell loop.
 * @info: Pointer to the info struct.
 * @av: Argument vector from main.
 *
 * Return: 0 on success, 1 on error.
 */
int shell_lp(info_t *info, char **av)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			custom_puts("$ ");
		shell_putchar(BUF_FLUSH);
		input_result = get_input(info);
		if (input_result != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin_command(info);
			if (builtin_result == -1)
				find_external_command(info);
		}
		else if (is_interactive(info))
			custom_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - Finds and executes a builtin command.
 * @info: Pointer to the info struct.
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *          2 if builtin signals exit().
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_result = -1;
	builtin_table builtins[] = {
		{"exit", shell_exit},
		{"env", shell_print_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_set_env},
		{"unsetenv", shell_unset_env},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].type; i++)
	{
		if (custom_strcmp(info->argv[0], builtins[i].type) == 0)
		{
			info->line_count++;
			builtin_result = builtins[i].func(info);
			break;
		}
	}
	return (builtin_result);
}

/**
 * find_external_command - Finds and executes an external command.
 * @info: Pointer to the info struct.
 *
 * Return: void.
 */
void find_external_command(info_t *info)
{
	char *cmd_path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], "\t\n"))
			j++;
	if(!j)
		return;

	cmd_path = find_executable_in_path(info, shell_get_env(info, "PATH="),
			info->argv[0]);
	if (cmd_path)
	{
		info->path = cmd_path;
		fork_and_execute_command(info);
	}
	else
	{
		if ((is_interactive(info) || shell_get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			fork_and_execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_custom_error(info, "not found\n");
		}
	}
}

/**
 * fork_and_execute_command - Forks and executes an external command.
 * @info: Pointer to the info struct.
 *
 * Return: void.
 */
void fork_and_execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		print_custom_error(info, "Permission denied\n");
	}
}

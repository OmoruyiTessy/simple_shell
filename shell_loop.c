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
			display_prompt();
		_eputchar(BUF_FLUSH);
		input_result = get_user_input(info);
		if (input_result != -1)
		{
			set_command_info(info, av);
			builtin_result = find_builtin_command(info);
			if (builtin_result == -1)
				find_external_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		cleanup_info(info, 0);
	}
	write_history_to_file(info);
	cleanup_info(info, 1);
	handle_noninteractive_mode(info, builtin_result);
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
	builtin_command builtins[] = {
		{"exit", execute_exit},
		{"env", execute_env},
		{"help", execute_help},
		{"history", execute_history},
		{"setenv", execute_setenv},
		{"unsetenv", execute_unsetenv},
		{"cd", execute_cd},
		{"alias", execute_alias},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].command; i++)
	{
		if (custom_strcmp(info->argv[0], builtins[i].command) == 0)
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
	int arg_count = count_non_empty_args(info->arg);

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	if (arg_count == 0)
		return;

	cmd_path = find_command_in_path(info, _getenv(info, "PATH="),
			info->argv[0]);
	if (cmd_path)
	{
		info->path = cmd_path;
		fork_and_execute_command(info);
	}
	else
	{
		if (should_execute_command(info))
		{
			info->status = 127;
			print_command_not_found_error(info);
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
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			cleanup_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait_and_set_exit_status(info);
	}
}

#include "shell.h"

/**
 * is_executable - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Returns: 1 if the file is an executable, 0 otherwise.
 */
int is_executable(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * extract_chars - Extracts characters from a string based on indices.
 * @source: The source string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Returns: A pointer to a new buffer containing the extracted characters.
 */
char *extract_chars(char *source, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (source[i] != ':')
			buffer[k++] = source[i];
	buffer[k] = '\0';
	return (buffer);
}

/**
 * find_executable_in_path - Finds the full path of a command in
 * the PATH environment.
 * @info: The info struct.
 * @pathstr: The PATH environment variable string.
 * @cmd: The command to find.
 *
 * Returns: The full path of the command if found, or NULL if not found.
 */
char *find_executable_in_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((custom_strlen(cmd) > 2) && custom_starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = extract_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

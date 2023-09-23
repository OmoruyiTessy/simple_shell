#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/* Read/Write Buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* To convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;

/**
 * struct builtin - contain a builtin string and their associated function
 * @type: the builtin command flag
 * @func: pointer to the corresponding function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;


/**
 * struct liststr - This singly linked list
 * @num: number field
 * @str: the string
 * @next: pointer to the next node in the list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - encapsulates pseudo-arguments intended for passing
 * into a function, ensuring a consistent function pointer struct prototype.
 * @alias: the alias node
 * @argc: The count of arguments.
 * @arg: A string derived from getline containing arguments.
 * @argv:An array of strings generated from arg
 * @cmd_buf: The address of a pointer to cmd_buf. It's set when
 * chaining commands.
 * @cmd_buf_type: Represents the command type (CMD_type) - ||, &&, or ;.
 * @env: A linked list, serving as a local copy of the environ variable.
 * @env_changed: A flag indicating whether environ has been modified.
 * @environ: A custom-modified copy of the environ variable derived from
 * the env linked list.
 * @err_num: The error code used for exit() calls.
 * @fname: The filename of the program.
 * @histcount: The count of history line numbers.
 * @history: the history node
 * @line_count: The count of encountered errors.
 * @linecount_flag: A flag indicating whether to count the current input line.
 * @path: A string representing the current command's path.
 * @readfd: The file descriptor from which to read line input.
 * @status: The return status of the last executed command.
 */
typedef struct passinfo
{
	list_t *alias;
	int argc;
	char *arg;
	char **argv;
	char **cmd_buf;
	int cmd_buf_type;
	list_t *env;
	int env_changed;
	char **environ;
	int err_num;
	char *fname;
	int histcount;
	list_t *history;
	unsigned int line_count;
	int linecount_flag;
	char *path;
	int readfd;
	int status;
} info_t;

#define INFO_INIT \
{NULL, 0, NULL, NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, \
		NULL, 0, 0}

/* shell_functions.c */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int string_to_integer(char *);

/* builtin.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* aliases.c */
int shell_history(info_t *);
int shell_alias(info_t *);

/* environ.c */
char *shell_get_env(info_t *, const char *);
int shell_print_env(info_t *);
int shell_set_env(info_t *);
int shell_unset_env(info_t *);
int shell_populate_env_list(info_t *);

/* string_utils.c */
void shell_puts(char *);
int shell_putchar(char);
int shell_putchar_fd(char c, int fd);
int shell_puts_fd(char *str, int fd);

/* err_output.c */
int str_to_int(char *);
void print_custom_error(info_t *, char *);
int shell_print_d(int, int);
char *int_to_str(long int, int, int);
void remove_comment(char *);

/* manipulation.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/*getline.c */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void handleCtrlC(int);

/* environment.c */
char **get_environ(info_t *);
int shell_unsetenv(info_t *, char *);
int shell_setenv(info_t *, char *, char *);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* linked_list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* list_helpers.c */
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* memory_helper.c */
int free_and_null(void **);

/* execute.c */
int is_executable(info_t *, char *);
char *extract_chars(char *, int, int);
char *find_executable_in_path(info_t *, char *, char *);

/* memory_operations.c */
char *custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* shell_loop.c */
int shell_lp(info_t *, char **);
int find_builtin_command(info_t *);
void find_external_command(info_t *);
void fork_and_execute_command(info_t *);

/* string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* string_functions.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* string_tokenizer.c */
char **split_string(char *, char *);
char **split_string_by_char(char *, char);

/* variables.c */
int is_chain_delimiter(info_t *, char *, size_t *);
void check_chain_continuation(info_t *, char *, size_t *, size_t, size_t);
int replace_aliases(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif/* SHELL_H */

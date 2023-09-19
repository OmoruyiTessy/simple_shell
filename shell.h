#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
extern int last_exit_status;

/**
 * struct Alias - Represent an alias structure
 * @name: the alias name
 * @value: the alias value
 * @next: pointer to the next alias in the list
 * This structure is used to define aliases in the shell.
 */
struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
};

/*Declare the global alias_list variable*/
void cleanupAliases(void);
extern struct Alias *alias_list;

/* Function prototypes */

/* getline.c */
char *custom_getline(void);

/* aliases.c */
void print_aliases(void);
void print_specific_aliases(char *names[], int name_count);
void add_alias(char *name, char *value);
void handleAliasCommand(char *input);
void executeInputCommand(char *input);

/* variables.c */
char *replace_variables(char *command);

/* execute.c */
int execute_command(char *command);

/* command.c */
void split_command(char *input, char *args[], int *arg_count);

#endif /* SHELL_H */

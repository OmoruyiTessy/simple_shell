#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

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
void cleanupAliases(struct Alias **alias_list);

/* Function prototypes */

/* getline.c */
char *custom_getline(void);

/* aliases.c */
void print_aliases(struct Alias *alias_list);
void print_specific_aliases(struct Alias *alias_list,
		char *names[], int name_count);
void add_alias(struct Alias **alias_list, char *name, char *value);
void handleAliasCommand(char *input, struct Alias **alias_list);
void executeInputCommand(char *input, struct Alias **alias_list);

/* variables.c */
char *replace_variables(char *command, int *last_exit_status);

/* execute.c */
int execute_command(char *command, int *last_exit_status);

/* command.c */
void split_command(char *input, char *args[], int *arg_count);

#endif /* SHELL_H */

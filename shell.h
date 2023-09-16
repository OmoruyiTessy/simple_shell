#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

/* commands.c */
void split_command(char *input, char *args[], int *arg_count);

#endif /* SHELL_H */

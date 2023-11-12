#ifndef SHELL_H
#define SHELL_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_SIZE 2024
#define MAX_ARG_SIZE 64

/**
 * struct command - Structure to represent a comand.
 * @name: The name of the command.
 * @args: Arrahy of arguments for the command.
 * @in_fd: Input file descriptor.
 * @out_fd: Output file desccriptor.
 * @next: Pointer to the next xommand in the linked list.
 */
typedef struct command
{
	char *name;
	char **args;
	int in_fd;
	int out_fd;
	struct command *next;
}
comand;

/* Function prototypes */
char **tokenize(char *input);
command *parse(char *input);
void execute(command *head);
void handle_error(cosnt char *msg);
void free_commands(command *head);

#endif  /* SHELL_H */

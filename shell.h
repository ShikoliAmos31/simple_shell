#ifndef SHELL_H
#define SHELL_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 2024
#define MAX_ARG_SIZE 64
#define PROMPT "haf and Amos cmd$"

extern char **environ;

/**
 * struct Shellinfo - Structure to hold the shell
 * @program_name: The name of the shelll comand.
 * @args: Array of arguments for the command.
 * @file _descriptor: Input file descriptor.
 * @out_fd: Output file desccriptor.
 * @next: Pointer to the next xommand in the linked list.
 * @alias: Field for storing aliases.
 */
typedef struct ShellInfo
{
	char *program_name;
	char **args;
	int file_descriptor;
	int out_fd;
	struct command *next;
	char *alias;
}
ShellInfo;

/**
 * struct builtin_command - Separate structure for built-in commands.
 * @name: The name of the built-in command.
 * @function: Function for executing the built-in command.
 */

typedef struct builtin_command
{
	char *name;
	void (*function)(char **args);
} builtin_command;

/* Function prototypes */

void display_prompt(char *prompt, ShellInfo *info);
int get_user_input(ShellInfo *info);
void execute_command(ShellInfo *info);
void handle_execution_error(ShellInfo *info);
void run_non_interactive_mode(ShellInfo *info);
void print_to_console(char *message);
void print_error_message(int error_code, ShellInfo *info);
#endif  /* SHELL_H */

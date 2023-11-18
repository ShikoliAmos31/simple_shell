#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define UNUSED(x) (void)(x)

extern char **environ;

#define MAX_INPUT_SIZE 1024
#define PROMPT "simple_shell$ "

typedef struct {
    char *name;
    int fd;
    char *input;
} ProgramInfo;

void _prompt(char *prompt, ProgramInfo *data);
int _getline(ProgramInfo *data);
void execute_command(ProgramInfo *data);
void handle_error(ProgramInfo *data);
void execute_non_interactive(ProgramInfo *data);

void _print(char *str);
void _print_error(int error_code);

int main(void) {
    ProgramInfo data_struct = {NULL};
    ProgramInfo *data = &data_struct;

    data->name = "simple_shell";
    data->fd = STDIN_FILENO;

    signal(SIGINT, SIG_IGN); /* Ignore Ctrl+C in non-interactive mode */

    if (!isatty(STDIN_FILENO)) {
        /* Non-interactive mode */
        execute_non_interactive(data);
    } else {
        /* Interactive mode */
        _prompt(PROMPT, data);
    }

    return 0;
}

void _prompt(char *prompt, ProgramInfo *data) {
    int error_code = 0, strings_len = 0;

    while (1) {
        _print(prompt);
        error_code = strings_len = _getline(data);

        if (error_code == EOF) {
            free(data->input);
            exit(0); /* Exit gracefully on Ctrl+D */
        }

        if (strings_len >= 1) {
            execute_command(data);
        }
    }
}

int _getline(ProgramInfo *data) {
    _print(PROMPT);
    data->input = malloc(MAX_INPUT_SIZE);

    if (!data->input) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (fgets(data->input, MAX_INPUT_SIZE, stdin) == NULL) {
        free(data->input);
        return EOF;
    }

    /* Remove the newline character from the input */
    data->input[strcspn(data->input, "\n")] = '\0';

    return strlen(data->input);
}

void execute_command(ProgramInfo *data) {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        handle_error(data);
    }

    if (child_pid == 0) {
        /* Child process */
        char *envp[] = {NULL}; /* An empty environment array */
        if (execve(data->input, (char *const *)environ, envp) == -1) {
            handle_error(data);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(child_pid, &status, 0);
    }
}

void handle_error(ProgramInfo *data) {
	 UNUSED(data); /* Avoid unused parameter warning */
    _print_error(1); /* Print error message */
    _print_error(1); /* Print prompt again */
}

void execute_non_interactive(ProgramInfo *data) {
    int error_code = 0, strings_len = 0;

    while (1) {
        error_code = strings_len = _getline(data);

        if (error_code == EOF) {
            free(data->input);
            exit(0); /* Exit gracefully on Ctrl+D */
        }

        if (strings_len >= 1) {
            execute_command(data);
        }
    }
}

void _print(char *str) {
    write(STDOUT_FILENO, str, strlen(str));
}

void _print_error(int error_code) {
    char error_message[MAX_INPUT_SIZE];
    snprintf(error_message, sizeof(error_message), "Error %d\n", error_code);
    write(STDERR_FILENO, error_message, strlen(error_message));
}


#include "shell.h"
#include <unistd.h>

/**
 * prints_program - program that prints names of the programers
 * Return: 0 on success
 */
int prints_program(void)
{
	write(STDOUT_FILENO, "Amos and Yusuf, program!\n", 26);
	return (0);
}

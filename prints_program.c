#include "shell.h"
#include <unistd.h>

/**
 * main - program that prints names of the programers
 * Return: 0 on success
 */
int main(void)
{
	write(STDOUT_FILENO, "Amos and Yusuf, program!\n", 26);
	return (0);
}

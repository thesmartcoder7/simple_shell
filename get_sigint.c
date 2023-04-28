#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * get_sigint - Handle the (ctrl + c) call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n#Simple_Shell$ ", 15);
}

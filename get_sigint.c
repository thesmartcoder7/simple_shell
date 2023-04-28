#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * get_sigint - Handle the (ctrl + c) call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	char *prompt;
	int length;
	(void)signal;

	prompt = _strcat(getlogin(), "@shell$ ");
	length = _strlen(_strcat(getlogin(), "@shell$ "));
	write(STDOUT_FILENO, prompt, length);
}

#include "../minishell.h"

void handle_signal(int signo)
{
	pid_t pid;
	int status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\b\b \b\b\n", STDOUT_FILENO);
			//printf_prompt();
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		else
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
}

void set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
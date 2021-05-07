#include "../minishell.h"


void		handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			printf("\b\b \b\b\n");
		}
		else
			printf("\n");
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			printf("\b\b  \b\b");
		else
			printf("Quit: 3\n");
	}
}

void		set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int main(int argc, char *argv[], char *envp[])
{
	int c;

	set_signal();
	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("input: %d\n", c);
	}
}
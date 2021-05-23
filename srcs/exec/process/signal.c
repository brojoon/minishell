#include "minishell.h"

void	printf_prompt(void)
{
	char	*prompt;

	prompt = get_prompt();
	ft_putstr_fd("\b\b  \b\b\n", STDOUT_FILENO);
	write(0, prompt, ft_strlen(prompt));
	free(prompt);
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
			printf_prompt();
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		g_status = 130;
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			return ;
		else
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		g_status = 131;
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

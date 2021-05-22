#include "minishell.h"

void	handle_signal(int signo)
{
	pid_t	pid;
	char	*prompt;
	int		status;

	prompt = get_prompt();
	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\b\b  \b\b\n", STDOUT_FILENO);
			write(0, prompt, ft_strlen(prompt));
		}
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		g_status = 130;
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			return ;
		else
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		g_status = 131;
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:04:02 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/28 15:25:10 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	pid = waitpid(-1, &g_bash.status, 0);
	if (signo == SIGINT)
	{
		if (pid == -1)
			printf_prompt();
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		g_bash.status = 130;
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			return ;
		else
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	}
	if (g_bash.status == 2)
		g_bash.status = 130;
	if (g_bash.status == 3)
		g_bash.status = 131;
}

void	set_signal(void)
{
	//signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

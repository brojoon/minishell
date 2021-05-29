/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:02:58 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:02:59 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg_join(char *arg1, char *arg2, char *arg3)
{
	char	*joined;

	joined = ft_strjoin(arg1, arg2);
	if (!joined)
		exit(1);
	catch_error(joined, arg3);
	free(joined);
}

void	catch_error(char *inst, char *msg)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(inst, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	set_g_status(void)
{
	if (g_bash.status == 256)
		g_bash.status = 127;
	else if (g_bash.status == 512)
		g_bash.status = 2;
	else if (g_bash.status == 768)
		g_bash.status = 1;
}

void	exec_error_handle(char *msg1, char *msg2, int status)
{
	catch_error(msg1, msg2);
	exit(status);
}

void	exit_status(int status)
{
	if (status == 1)
		status = 3;
	exit(status);
}

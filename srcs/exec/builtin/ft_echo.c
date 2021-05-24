/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:49:47 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:50:47 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_inst *proc, char *op)
{
	t_string	*arg;

	arg = proc->arg;
	g_status = 0;
	if (arg == NULL || arg->str == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return ;
	}
	while (arg && arg->str)
	{
		ft_putstr_fd(arg->str, STDOUT_FILENO);
		arg = arg->next;
	}
	if (op == NULL || ft_strcmp(op, "-n") != 0)
		ft_putendl_fd("", STDOUT_FILENO);
	return ;
}

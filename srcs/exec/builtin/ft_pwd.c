/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:52:24 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:52:26 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	if (!(getcwd(buf, 1024)))
	{
		catch_error("pwd", strerror(errno));
		g_status = 1;
	}
	else
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		g_status = 0;
	}
	return ;
}

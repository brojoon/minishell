/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:21:30 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 18:21:55 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_redir_type(t_string *rd)
{
	int	i;

	i = 0;
	if (rd && rd->str)
	{
		while (rd->str[i] && !(ft_strchr("><", rd->str[i])))
			i++;
		if (rd->str[i])
		{
			if (rd->str[i] == '>')
			{
				if (rd->str[i + 1] == '>')
					return (DRIGHT);
				return (RIGHT);
			}
			else
				return (LEFT);
		}
	}
	return (0);
}

int		get_redir_fd(t_string *rd, int type)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (ft_isdigit(rd->str[i]))
	{
		num = num * 10 + (rd->str[i] - '0');
		i++;
	}
	if (i == 0)
		return (type);
	return (num);
}

void	add_shlvl(t_env *env)
{
	int i;

	i = ft_atoi(env->value);
	free(env->value);
	i++;
	env->value = ft_itoa(i);
}

int		execve_before_term(char *path, char **args, \
char **envs, t_cursor *cursor)
{
	int ret;

	recover_term(cursor);
	ret = execve(path, args, envs);
	init_term(cursor);
	return (ret);
}

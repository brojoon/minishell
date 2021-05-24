/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:52:34 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:29:14 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_first(t_env **envs)
{
	t_env		*tmp;

	tmp = (*envs)->next;
	free((*envs)->key);
	free((*envs)->value);
	free(*envs);
	(*envs) = tmp;
	g_status = 0;
}

void		del_env(char *key, t_env *envs)
{
	t_env		*tmp;
	t_env		*cur;

	cur = envs;
	while (cur && cur->key)
	{
		if (!ft_strcmp(cur->key, key))
		{
			tmp = cur->next;
			while (envs->next != cur)
				envs = envs->next;
			envs->next = tmp;
			free(cur->key);
			free(cur->value);
			free(cur);
			cur = NULL;
			break ;
		}
		cur = cur->next;
	}
	g_status = 0;
}

int			check_valid_env_key(char *key)
{
	if (!key)
		return (0);
	if (ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void		ft_unset(t_inst *proc, t_env **envs)
{
	char		*err_msg;
	char		*tmp;
	t_string	*arg;

	arg = proc->arg;
	if (!(*envs) || !arg)
		return ;
	while (arg)
	{
		if (!check_valid_env_key(arg->str))
		{
			tmp = ft_strjoin("`", arg->str);
			err_msg = ft_strjoin(tmp, "\': not a valid identifier");
			catch_error(proc->inst, err_msg);
			free(tmp);
			free(err_msg);
			g_status = 1;
			break ;
		}
		else if (!ft_strcmp((*envs)->key, arg->str))
			del_first(envs);
		else
			del_env(arg->str, *envs);
		arg = arg->next;
	}
}

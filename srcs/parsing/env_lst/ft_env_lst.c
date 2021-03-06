/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:57:44 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:57:46 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envfree(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_envadd_back(t_env **root, t_env *now)
{
	t_env	*curr;

	if (*root == 0)
		*root = now;
	else
	{
		curr = *root;
		while (curr->next)
			curr = curr->next;
		curr->next = now;
	}
}

t_env	*ft_envinit(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == 0)
		return (0);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = 0;
	return (env);
}

void	set_genv(t_env **root, char **envp)
{
	char	**chunk;
	char	**curr;
	int		cnt_args;
	t_env	*temp;

	curr = envp;
	while (*curr)
	{
		chunk = ft_split(*curr, '=');
		cnt_args = ft_cnt_lines(*curr, '=');
		if (cnt_args == 2)
			temp = ft_envinit(chunk[0], chunk[1]);
		else
			temp = ft_envinit(chunk[0], "");
		ft_envadd_back(root, temp);
		ft_free_chunks(chunk, cnt_args);
		curr++;
	}
}

void	free_genv(t_env *env)
{
	t_env	*del;
	t_env	*curr;

	curr = env;
	del = curr;
	while (del != 0)
	{
		curr = del->next;
		ft_envfree(del);
		del = curr;
	}
}

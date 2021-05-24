/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:52:12 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:52:14 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_value(char **tmp, t_env *envs)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (tmp[++i])
	{
		tmp2 = ft_strjoin(envs->value, tmp[i]);
		free(envs->value);
		envs->value = tmp2;
		free(tmp[i]);
		if (tmp[i + 1])
		{
			tmp2 = ft_strjoin(envs->value, "=");
			free(envs->value);
			envs->value = tmp2;
		}
	}
	free(tmp[i]);
}

void	add_export(char *str, t_env *envs)
{
	char	**tmp;

	tmp = ft_split(str, '=');
	while (envs && envs->next && ft_strcmp(tmp[0], envs->key))
		envs = envs->next;
	if (!ft_strcmp(tmp[0], envs->key))
		free(envs->value);
	else
	{
		envs->next = (t_env *)malloc(sizeof(t_env));
		envs = envs->next;
		envs->key = tmp[0];
		envs->next = NULL;
	}
	envs->value = ft_strdup("");
	handle_value(tmp, envs);
	free(tmp);
}

void	value_is_null(char *str, t_env *envs)
{
	while (envs && envs->next && ft_strcmp(str, envs->key))
		envs = envs->next;
	if (ft_strcmp(str, envs->key))
	{
		envs->next = (t_env *)malloc(sizeof(t_env));
		envs->next->key = ft_strdup(str);
		envs->next->value = NULL;
		envs->next->next = NULL;
	}
}

void	append_export(char *str, t_env *envs)
{
	char	*tmp;
	char	*value;
	int		len;

	len = ft_strchr(str, '+') - str;
	tmp = ft_substr(str, 0, len);
	value = ft_substr(str, len + 2, ft_strlen(str));
	while (envs && envs->next && ft_strcmp(tmp, envs->key))
		envs = envs->next;
	if (!ft_strcmp(tmp, envs->key))
	{
		free(tmp);
		tmp = ft_strjoin(envs->value, value);
		free(envs->value);
		free(value);
		envs->value = tmp;
	}
	else
	{
		envs->next = (t_env *)malloc(sizeof(t_env));
		envs->next->key = tmp;
		envs->next->value = value;
		envs->next->next = NULL;
	}
}

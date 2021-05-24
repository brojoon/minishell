/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:03:55 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:03:56 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(char *key, t_env *envs)
{
	while (envs)
	{
		if (!ft_strcmp(envs->key, key))
			return (envs->value);
		envs = envs->next;
	}
	return (0);
}

void	ft_free_split(char **paths)
{
	int	i;

	i = -1;
	if (paths)
	{
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
}

char	*get_path(char *inst, t_env *envs)
{
	int			i;
	char		*tmp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	tmp = find_value("PATH", envs);
	paths = ft_split(tmp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", inst);
		new_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(new_path, &s) == 0)
		{
			ft_free_split(paths);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	ft_free_split(paths);
	return (ft_strdup(inst));
}

char	**envs_to_chunks(t_env *envs)
{
	int		size;
	char	**chunks;
	char	*tmp;
	char	*tmp2;

	size = get_envs_size(envs);
	chunks = (char **)malloc(sizeof(t_env) * size + 1);
	size = 0;
	while (envs && envs->key)
	{
		if (envs->value)
		{
			tmp = ft_strjoin(envs->key, "=");
			tmp2 = ft_strjoin(tmp, envs->value);
			chunks[size] = tmp2;
			free(tmp);
		}
		else
			chunks[size] = ft_strdup(envs->key);
		size++;
		envs = envs->next;
	}
	chunks[size] = NULL;
	return (chunks);
}

void	print_status(void)
{
	char	*str;

	str = ft_itoa(g_status);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	free(str);
	g_status = 127;
}

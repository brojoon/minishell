#include "minishell.h"

t_env	*get_env(t_env *envs, char *key)
{
	while (envs)
	{
		if (envs->key)
			if (ft_strcmp(envs->key, key) == 0)
				return (envs);
		envs = envs->next;
	}
	return (0);
}

void	edit_env_value(t_env *envs, char *key, char *value)
{
	while (envs)
	{
		if (envs->key)
		{	
			if (ft_strcmp(envs->key, key) == 0)
			{
				free(envs->value);
				envs->value = value;
				break ;
			}	
		}
		envs = envs->next;
	}
}

void	ft_env(t_env *envs)
{
	t_env	*node;

	node = envs;
	g_status = 0;
	while (node)
	{
		if (node->key && node->value)
		{
			ft_putstr_fd(node->key, STDOUT_FILENO);
			if (node->value)
			{
				ft_putstr_fd("=", STDOUT_FILENO);
				ft_putstr_fd(node->value, STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		node = node->next;
	}
	return ;
}
